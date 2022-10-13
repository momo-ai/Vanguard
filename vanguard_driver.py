#!/usr/bin/env python3

import argparse
import dataclasses
import enum
import os
import re
import shutil
import subprocess
import sys
import tempfile
from collections import defaultdict

# from tabulate import tabulate
from pathlib import Path
from typing import Dict, List, Literal, Union

############################
# Detectors
############################
DETECTORS = ["statGen", "fnPrinter", "Reentrancy", "irValidator"]


def solidity_summarizer_cmd(sol_file: Path):
    return ["solidity-summarizer", str(sol_file)]


############################
# Extensions
############################


class Platform(enum.Enum):
    SOLIDITY = "solidity"
    RUST = "rust"


SRC_FILE_EXTENTIONS = {
    ".sol": Platform.SOLIDITY,
    ".rs": Platform.RUST,
}


def get_per_func_info(s: str):
    patt = re.compile("(Function '([^']*)' [^\n]*)")
    matches = patt.findall(s)

    return matches


@dataclasses.dataclass
class VanguardDriverOpts:
    """CLI options for the Vanguard driver."""

    src_path: Path
    detectors: List[str]
    create_ir: bool
    output_dir: Path

    # Whether to "clean" compile
    clean: bool


def preprocess_file(args: VanguardDriverOpts, lang: Platform, ext: str):
    """Run any instrumentation/preprocessing needed to convert to LLVM."""

    if lang == Platform.SOLIDITY:

        def is_cached(out_path: Path, src_path: Path) -> bool:
            return (
                out_path.exists()
                and out_path.stat().st_mtime >= src_path.stat().st_mtime
            )

        # hack to prevent solc-typed-ast from writing to the Nix store
        # TODO: move this to the flake
        solc_env: Dict[str, str] = {}
        solc_env.update(os.environ)
        solc_env["SOL_AST_COMPILER_CACHE"] = "/tmp/solc-typed-ast"

        # Run summarizer and save result to json
        summarizer_cmd = solidity_summarizer_cmd(args.src_path)
        summary_name = args.src_path.stem + "_deploy_summary.json"
        summary_path = args.output_dir / summary_name

        if not is_cached(summary_path, args.src_path):
            with open(summary_path, "wb") as f:
                print("Running Solidity summarizer...", end="", flush=True)
                summary = subprocess.check_output(
                    summarizer_cmd, stderr=subprocess.DEVNULL, env=solc_env
                )
                f.write(summary)
                print(f"Completed Solidity summarizer, summary at {summary_path}.")
        else:
            print(f"Using cached summary at {summary_path}.")

        # Run preprocessor and save result to json
        preprocessed_name = f"{args.src_path.stem}_instrumented{args.src_path.suffix}"
        preprocessed_path = args.output_dir / preprocessed_name

        if not is_cached(preprocessed_path, args.src_path):
            preprocessor_cmd = ["solidity-preprocessor", str(args.src_path)]
            with open(preprocessed_path, "wb") as f:
                print("Running Solidity preprocessor...", end="", flush=True)
                preprocessed = subprocess.check_output(
                    preprocessor_cmd, stderr=subprocess.DEVNULL, env=solc_env
                )
                f.write(preprocessed)
                print(
                    "Completed Solidity preprocessor, preprocessed version at {}.".format(
                        preprocessed_path
                    )
                )
        else:
            print(f"Using cached preprocessed version at {preprocessed_path}.")

        def mk_solang_cmd(
            out_type: Literal["llvm-ir", "llvm-bc"], src_path: Path, out_dir: Path
        ):
            """Generate commandline command for Solang."""
            return [
                "solang",
                str(src_path),
                "--target",
                "ewasm",
                "--emit",
                out_type,
                "-o",
                str(out_dir),
            ]

        solang_cmd = mk_solang_cmd("llvm-bc", preprocessed_path, args.output_dir)

        # Run solang
        print("Running Solang...", end="")
        subprocess.check_output(solang_cmd, stderr=subprocess.DEVNULL)
        print(
            "Completed Solang, compiled files in folder at {}".format(args.output_dir)
        )
    elif lang == "rust":
        raise NotImplementedError

    return summary_path


def run_detector(detector: str, summary_path: Path, out_dir: Path) -> Dict[str, str]:
    """Execute the Vanguard detector program on the .bc files in out_dir."""
    results = {}
    for bc_path in out_dir.glob("**/*_deploy.bc"):
        class_name = bc_path.name.replace("_deploy.bc", "")
        print("Running Vanguard on class {}...".format(class_name), end="")
        vanguard_cmd: List[Union[str, Path]] = [
            "Vanguard",
            bc_path,
            "--detectors",
            detector,
        ]
        proc = subprocess.run(
            vanguard_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
        )
        if proc.returncode != 0:
            print("Got error from Vanguard!")
            print(proc.stderr)
            return results

        print("Completed Vanguard.")
        results[class_name] = proc.stdout

    return results


# def print_results(results):
#    out = [["Class", "Detector", "Function Flagged by Detector", "Detailed Output"]]
#    for cls, ress in results.items():
#        for info in ress:
#            detector, res = info
#            parsed_res = get_per_func_info(res)
#            for note, func in parsed_res:
#                simple_func = func.split("::")[-1].split("__")[0]
#                row = [cls, detector, simple_func, note]
#                out.append(row)

#    print(tabulate(out, tablefmt="grid"))


def print_results(results):
    for cls, ress in results.items():
        for info in ress:
            detector, res = info
            print("--------- {} ---------".format(detector))
            print(res)


def run(args: VanguardDriverOpts):
    """Run the Vanguard driver application."""
    # Remove existing outputs
    if args.output_dir.exists() and args.clean:
        shutil.rmtree(args.output_dir)
    args.output_dir.mkdir(exist_ok=True)
    assert args.output_dir.exists()

    ext = args.src_path.suffix
    if ext not in SRC_FILE_EXTENTIONS:
        sys.exit(f"File extension {ext} not recognized!")

    lang = SRC_FILE_EXTENTIONS[ext]

    print(f"----Preprocessing {args.src_path}----")
    summary_path = preprocess_file(args, lang, ext)

    results = defaultdict(list)
    for detector in args.detectors:
        print(f"----Running {args.src_path} with {detector} detector----")
        detector_results = run_detector(detector, summary_path, args.output_dir)
        for cls, res in detector_results.items():
            results[cls].append((detector, res))

    print("----VANGUARD REPORT----")
    print_results(results)


def main():
    """Application entrypoint."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--src_path",
        help="path to program to run (default is None)",
        type=Path,
        required=True,
    )
    parser.add_argument(
        "--detector",
        help="choose benchmark to curate (default is None, 'all' will run all detectors)",
        type=str,
        required=True,
    )
    parser.add_argument(
        "--create_ir",
        help="enables output of ir in addition to bc files",
        action="store_true",
    )
    parser.add_argument(
        "-o",
        "--output-dir",
        type=Path,
        help="output directory (default is temporary directory)",
        default=None,
    )
    parser.add_argument(
        "--clean",
        help="remove the output directory if it exists",
        action="store_true",
    )
    args = parser.parse_args()

    if not args.src_path.exists():
        sys.exit(f"Source path {args.src_path} does not exist!")

    if args.detector not in DETECTORS and args.detector != "all":
        sys.exit(
            f"{args.detector} is not a recognized detector (check DETECTORS at top of run.py)!"
        )

    if args.output_dir is None:
        tmpd = tempfile.TemporaryDirectory(args.output_dir)
        args.output_dir = Path(tmpd.name)

    if args.detector == "all":
        detectors = DETECTORS
    else:
        detectors = [args.detector]

    opts = VanguardDriverOpts(
        src_path=args.src_path,
        detectors=detectors,
        create_ir=args.create_ir,
        output_dir=args.output_dir,
        clean=args.clean,
    )
    run(opts)


if __name__ == "__main__":
    main()
