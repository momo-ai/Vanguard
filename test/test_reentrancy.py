from collections import defaultdict
import json
import os
import re
import subprocess
from tabulate import tabulate
from typing import *

TYPES = ["reentrancy", "suicide", "uninitialized_state"]
TESTS_PATH = os.path.join("test")
OPT_PATH = os.path.join("/", "opt", "homebrew", "Cellar", "llvm", "13.0.1_1", "bin", "opt")
OPT_CMD = "{} --load=cmake-build-debug/lib/libVanguard.dylib -enable-new-pm=0 --summary={{}} --{{}} {{}} -o /dev/null".format(OPT_PATH)

def run():
    results = defaultdict(dict)
    for typ in TYPES:
        print("Running {} tests!".format(typ))
        for typ2 in TYPES:
            typ_tests_path = os.path.join(TESTS_PATH, "{}_tests".format(typ2))
            run_typ(typ, typ_tests_path, results)

    print("RESULTS")
    out_res = [["File"] + ["Functions with Potential Unsafe {}".format(typ) for typ in TYPES]]
    for test, typ_res in results.items():
        row = ["{}.sol".format(test)] + [""]*len(TYPES)
        for typ, res in typ_res.items():
            row[TYPES.index(typ)+1] = "\n".join([r[1].split("::")[-1] for r in res])
        out_res.append(row)

    print(tabulate(out_res, tablefmt="grid"))
    # print(json.dumps(out_res))

def get_per_func_info(s: str):
    patt = re.compile("(Function '([^']*)' [^\n]*)")
    matches = patt.findall(s)

    return matches

def run_typ(typ: str, typ_tests_path: str,
            results: Dict[str, Dict[str, List[Tuple[str, str]]]]):
    tests = os.listdir(typ_tests_path)
    tnames = set(["_".join(t.split("_")[:-1]) for t in tests]) # Get unique test names

    for test in tnames:
        print("\tRunning file {}!".format(test))
        bc_path = os.path.join(typ_tests_path, "{}_deploy.bc".format(test))
        summary_path = os.path.join(typ_tests_path, "{}_summary.json".format(test))
        opt_cmd = OPT_CMD.format(summary_path, typ, bc_path)
        # print(opt_cmd)
        tout = bytes.decode(subprocess.check_output(opt_cmd.split()))
        results[test][typ] = get_per_func_info(tout)

if __name__=="__main__":
    run()