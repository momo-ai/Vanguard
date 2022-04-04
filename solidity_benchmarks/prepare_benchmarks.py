import argparse as ap
import os
import shutil
import subprocess

BMARKS = ["reentrancy", "suicide", "unchecked_transfer", "uninitialized_state", "msg_value_loop", "delegatecall_loop", "tainted_send"]

SRC_DIR="examples"
OUT_DIR="processed_examples"

SOLANG=os.path.join("/", "Users", "bmariano", "veridise", "solang", "target", "release", "solang")
PREPROCESSOR=os.path.join("/", "Users", "bmariano", "veridise", "SolidityPreprocessor", "src", "preprocess.js")

IR_SOLANG_CMD="{} --target ewasm --emit llvm-ir -o {{}} {{}}".format(SOLANG)
BC_SOLANG_CMD="{} --target ewasm --emit llvm-bc -o {{}} {{}}".format(SOLANG)
PREPROCESSOR_CMD="node {} {{}}".format(PREPROCESSOR)

def make_benchmarks(name, args):
    bmarks_path = os.path.join(SRC_DIR, name)
    assert(os.path.exists(bmarks_path))

    out_path = os.path.join(OUT_DIR, name)
    os.makedirs(out_path)

    for bmark in os.listdir(bmarks_path):
        bmark_path = os.path.join(bmarks_path, bmark)
        print("Processing {}".format(bmark_path))

        out_name = bmark.replace(".sol", "_summary.json")
        if args.create_ir:
            solang_cmd = IR_SOLANG_CMD.format(out_path, bmark_path)
        else:
            solang_cmd = BC_SOLANG_CMD.format(out_path, bmark_path)
        preprocessor_cmd = PREPROCESSOR_CMD.format(bmark_path,out_path)

        # Run solang
        subprocess.check_output(solang_cmd.split())

        # Run preprocessor and save result to json
        with open(os.path.join(out_path, out_name), "wb") as f:
            summary = subprocess.check_output(preprocessor_cmd.split())
            f.write(summary)

def prepare(args):
    if os.path.exists(OUT_DIR):
        # Remove existing output
        shutil.rmtree(OUT_DIR)

    # Make output director
    os.makedirs(OUT_DIR)

    assert(os.path.exists(SRC_DIR))

    if args.bmark == None:
        bmarks = BMARKS
    else:
        bmarks = [args.bmark]
    for bmark in bmarks:
        print("Curating {} benchmarks!".format(bmark))
        print("--"*8)
        make_benchmarks(bmark, args)

if __name__=="__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("--create_ir", help="enables output of ir instead of bc", action="store_true")
    parser.add_argument("--bmark", help="choose benchmark to curate", type=str, default=None)
    args = parser.parse_args()
    prepare(args)
