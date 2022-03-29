import os
import subprocess

TESTS_PATH = os.path.join("test", "reentrancy_tests")
OPT_PATH = os.path.join("/", "opt", "homebrew", "Cellar", "llvm", "13.0.1_1", "bin", "opt")
OPT_CMD = "{} --load=cmake-build-debug/lib/libVanguard.dylib -enable-new-pm=0 --summary={{}} --reentrancy {{}} -o /dev/null".format(OPT_PATH)

def run():
    tests = os.listdir(TESTS_PATH)
    tnames = set([t.split("_")[0] for t in tests]) # Get unique test names

    for test in tnames:
        bc_path = os.path.join(TESTS_PATH, "{}_deploy.bc".format(test))
        summary_path = os.path.join(TESTS_PATH, "{}_summary.json".format(test))
        opt_cmd = OPT_CMD.format(summary_path, bc_path)
        print(opt_cmd)
        tout = subprocess.check_output(opt_cmd.split())
        print(tout)

if __name__=="__main__":
    run()