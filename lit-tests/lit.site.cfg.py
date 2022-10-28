# This is the lit test configuration for end-to-end tests.
# - yul2llvm_cpp must be on path
# - pyul must be on path

from pathlib import Path
import subprocess
import shutil
import tempfile

# test_source_root: The root path where tests are located.
config.test_source_root = Path(__file__).parent

config.llvm_tools_dir = subprocess.check_output(['llvm-config', '--bindir'],
                                                     text=True).rstrip()

vanguardExec_path = shutil.which('Vanguard')
if vanguardExec_path is None:
    # Check for in-source build
    vanguardExec_path = config.test_source_root.parent / "build" / "lib" / "Vanguard" 
    vanguardExec_path = vanguardExec_path.resolve() if vanguardExec_path.exists() else None
assert vanguardExec_path is not None, 'vanguardExec_path not found on PATH'
# pyul_path = shutil.which('pyul')  
# assert pyul_path is not None, 'pyul not found on PATH'    # no need for pyul as Vanguard_cpp is everything

config.cpp_bin_dir = str(Path(vanguardExec_path).parent)

config.extra_suffixes = []

import lit.llvm
lit.llvm.initialize(lit_config, config)

def _run_lit():
    # Let the main config do the real work.
    lit_config.load_config(config, config.test_source_root / "lit.cfg.py")

# test_exec_root: The root path where tests should be run.
override_test_exec_root = os.environ.get('VANGUARD_TEST_RUN', None)
if override_test_exec_root is None:
    with tempfile.TemporaryDirectory(prefix='Vanguard_e2e_test') as test_exec_root:
        config.test_exec_root = test_exec_root
        _run_lit()
else:
    assert Path(override_test_exec_root).is_dir()
    config.test_exec_root = override_test_exec_root
    _run_lit()
