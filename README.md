# Vanguard

Vanguard is an open-source static analyzer for finding bugs in Smart Contracts. Vanguard detects common vulnerabilities 
in a *blockchain-agnostic* way by targetting any smart contract language (e.g., Solidity, Rust, etc.) that 
can be compiled to LLVM.

- [Usage](#usage)
- [How to Install](#how-to-install)
- [Detectors](#detectors)
- [Documentation](#documentation)
- [Adding a Detector](#adding-a-detector)
- [Common Errors](#common-errors)

## Usage

### Python Script

To run Vanguard on a smart contract, you can simply run the following command:

```bash
python3 vanguard_driver.py --src_path=<PATH_TO_SMART_CONTRACT> --detector=<NAME_OF_DETECTOR>
```

where `<PATH_TO_SMART_CONTRACT>` is the path to the contract to be analyzed, and
`<NAME_OF_DETECTOR>` is the name of the detector to be run (e.g., `reentrancy`).
To run all available detectors on the contract, use the detector name `all`.

As an example, running this command:
```bash
python3 vanguard_driver.py --src_path test/PuppetPool.sol --detector statGen
```
should produce the following result:
```bash
----Preprocessing test/PuppetPool.sol----
Running Solidity summarizer...Completed Solidity summarizer, summary at /Users/jon/Documents/veridise/vanguard-v1/processed_examples/PuppetPool_summary.json.
Running Solidity preprocessor...Completed Solidity preprocessor, preprocessed version at /Users/jon/Documents/veridise/vanguard-v1/processed_examples/PuppetPool_instrumented.sol.
Running Solang...Completed Solang, compiled files in folder at /Users/jon/Documents/veridise/vanguard-v1/processed_examples
----Running test/PuppetPool.sol with statGen detector----
Running Vanguard on class PuppetPool...Completed Vanguard.
----VANGUARD REPORT----
--------- statGen ---------
Statistics:
# Functions: 101
# Basic Blocks: 462
# Instructions: 3316
```

If you need to debug the output of the driver application, you can add the `-o
<PATH_TO_DIR>` argument to have the driver script dump all of the intermediate
files in the provided directory. By default, the output dir will be set to a
temporary file that will be deleted when the driver script exits.

If the output directory is specified, the driver script will not delete the
output directory by default so that it can cache the intermediate outputs. For
convenience, the `--clean` argument can be used to delete the output directory
before running through the pipeline.

### Vanguard (for running on compiled LLVM bytecode)

To run a particular detector on a compiled LLVM bytecode file, run the following:

```bash
<PATH_TO_VANGUARD>/Vanguard --detectors "<DETECTORS>" --summary <CONTRACT_SUMMARY> [LLVM_Bytecode_Files]
```

where `<PATH_TO_VANGUARD>` is the path to the vanguard executable (so, if running from the Vanguard folder, 
this should be `build/lib/Vanguard`). `<DETECTORS>` is the list of detectors to run, as a comma separated list. 
`<CONTRACT_SUMMARY>` is a `JSON` file specifying contract specific information;
summaries can be generated for Solidity and Rust contracts using the following tools 
respectively: [SolidityPreprocessor](https://github.com/Veridise/SolidityPreprocessor) 
and [RustPreprocessor](https://github.com/Veridise/RustPreprocessor). 
Finally, `<LLVM_Bytecode_Files>` is the path to one or more `.bc` file to be analyzed.

## How to Install

There are three methods that you can use: Nix (preferred), Docker, and build from source.

### Nix

This repository contains a Nix flake that sets up the environment. However,
because submodules are used, you must add a flag to Nix to build correctly.

To build, use `nix build '.?submodules=1#vanguard`.

To launch a developer shell, use `nix develop '.?submodules=1'`. Once you are in
the developer shell, you can run the following commands:
* Generate CMake configuration: `phases=configurePhase genericBuild`
* Maintain the driver script
  * Run mypy: `mypy vanguard_driver.py`
  * Format the driver script: `black vanguard_driver.py && isort --profile black vanguard_driver.py`

### Docker

You can build the Docker image from this [Dockerfile](https://github.com/Veridise/Vanguard/blob/main/Dockerfile) and 
enter an interactive shell in the image using the following commands (note building will take around 10 minutes):

```bash
docker build -t vanguard .
docker run -i -t vanguard /bin/bash
```

For more help with Docker, checkout the [Docker documentation](https://docs.docker.com/).

### Build from Source

Vanguard has the following dependencies:
 * LLVM (Version 13.0.01)
 * CMake (Version 3.22.3)
 * Typescript (Version 4.6.3)
 * Node.js (Version 17.8.0)
 * Python3 (Version 3.8.9)
   * Tabulate
 * Cargo (Version 1.60.0)
 * Solang (Version 0.1.10-19-ga524ff5)
 * Z3 (Version 4.8.8, unless on MacOS ARM, then use 4.9.1)
   * If building from source, make sure to follow the cmake [build instructions](https://github.com/Z3Prover/z3/blob/master/README-CMake.md).

First, make sure all above depenencies are installed and the following executables are avaiable on the `$PATH`:
 * cmake
 * make
 * npm
 * node
 * tsc
 * opt
 * llvm-as
 * python3
 * cargo
 * solang

Vanguard also depends on [SVF (Version 2.5)](https://github.com/SVF-tools/SVF/tree/SVF-2.5). However, Vanguard requires a few minor modifications in SVF prior building. To properly build SVF you can run the following::

```bash
export LLVM_HOME=<LLVM_HOME_DIR>
./aux-build-scripts/build-svf.sh
```

Finally, to build Vanguard, simply run the following instructions.

```bash
export LLVM_HOME=<LLVM_HOME_DIR>
export SVF_HOME=<PARH_TO_VANGUARD_REPO>/deps/SVF # Created by build-svf.sh script
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```
## Detectors

Below is a list of detectors that are available in Vanguard. More detailed information with examples can be found in 
the extended [detector documentation](https://github.com/Veridise/Vanguard/wiki/Detectors).

| Name                 | Description                                    | Severity |
|----------------------|------------------------------------------------|----------|
| statGen              | Prints out IR statictics                       | Test     |
| fnPrinter            | Prints all function names                      | Test     |


## Adding a Detector

To add a detector, do the following:
1. Create a new directory in detectors for the new detector
2. To create the detector, extend the appropriate base detector. Currently there are: ProgramDetector, UnitDetector and FunctionDetector.
3. Add add_subdirectory(DETECTOR_DIR) to lib/detectors/CMakeLists.txt
4. Add a CMakeLists.txt in /lib/detectors/DETECTOR_DIR that adds target_sources to Vanguard
5. In DetectorRegistry.cpp, add the detector to the registry in the constructor.
6. Add the detector name to list DETECTORS in run.py.






