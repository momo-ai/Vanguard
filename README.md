# Vanguard

Vanguard is an open-source static analyzer for finding bugs in Smart Contracts. Vanguard detects common vulnerabilities 
in a *blockchain-agnostic* way by targetting any smart contract language (e.g., Solidity, Rust, etc.) that 
can be compiled to LLVM.

- [Usage](#usage)
- [How to Install](#how-to-install)
- [Detectors](#detectors)
- [Documentation](#documentation)

## Usage

### Python Script

To run Vanguard on a smart contract, you can simply run the following command:

```bash
python3 run.py --src_path=<PATH_TO_SMART_CONTRACT> --detector=<NAME_OF_DETECTOR>
```

where `<PATH_TO_SMART_CONTRACT>` is the path to the contract to be analyzed, and `<NAME_OF_DETECTOR>` is the name 
of the detector to be run (e.g., `reentrancy`). To run all available detectors on the contract, use the detector name `all`.

As an example, running this command:
```bash
python3 run.py --src_path=solidity_benchmarks/examples/reentrancy/reentrant1.sol --detector=reentrancy
```
should produce the following result:
```bash
----Preprocessing solidity_benchmarks/examples/reentrancy/reentrant1.sol----
Running Solidity summarizer...Completed Solidity summarizer, summary at processed_examples/reentrant1_summary.json.
Running Solidity preprocessor...Completed Solidity preprocessor, preprocessed version at processed_examples/reentrant1_instrumented.sol.
Running Solang...Completed Solang, compiled files in folder at processed_examples
----Running solidity_benchmarks/examples/reentrancy/reentrant1.sol with reentrancy detector----
Running Vanguard on class reentrant1...Completed Vanguard.
----VANGUARD REPORT----
+------------+------------+------------------------------+-----------------------------------------------------------------------------------------------------+
| Class      | Detector   | Function Flagged by Detector | Detailed Output                                                                                     |
+------------+------------+------------------------------+-----------------------------------------------------------------------------------------------------+
| reentrant1 | reentrancy | withdraw                     | Function 'reentrant1::reentrant1::function::withdraw' has potential reentrancy after call to 'call' |
+------------+------------+------------------------------+-----------------------------------------------------------------------------------------------------+
```

### Opt (for running on compiled LLVM bytecode)

To run a particular detector on a compiled LLVM bytecode file, run the following:

```bash
opt -load-pass-plugin=<PATH_TO_LIBVANGUARD> --passes="<DETECTORS>" -disable-output <PATH_TO_LLVM_BYTECODE> -o /dev/null
```

where `<PATH_TO_LIBVANGUARD>` is the path to the vanguard `.dylib`/`.so` file (so, if running from the Vanguard folder, 
this should be `build/lib/libVanguard.dylib`). `<DETECTORS>` is the list of detectors to run, each of which can be 
specified via `--<DETECTOR_NAME>`. `<CONTRACT_SUMMARY>` is a `JSON` file specifying contract specific information; 
summaries can be generated for Solidity and Rust contracts using the following tools 
respectively: [SolidityPreprocessor](https://github.com/Veridise/SolidityPreprocessor) 
and [RustPreprocessor](https://github.com/Veridise/RustPreprocessor). 
Finally, `<PATH_TO_LLVM_BYTECODE>` is the path to the `.bc` file to be analyzed.

## How to Install

### Docker

You can build the Docker image from this [Dockerfile](https://github.com/Veridise/Vanguard/blob/main/Dockerfile) and enter an interactive shell in the image using the following commands (note building will take around 10 minutes):

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

To build, simply run the following instructions.

```bash
export LLVM_HOME=<LLVM_HOME_DIR>
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```
## Detectors

Below is a list of detectors that are available in Vanguard. More detailed information with examples can be found in the extended [detector documentation](https://github.com/Veridise/Vanguard/wiki/Detectors).

| Name                  | Description                                     | Severity |
| --------------------  | ----------------------------------------------- | -------- |
| reentrancy            | Detects possible reentrancy attacks.            | High     |
| flashloan             | Detects possible flashloan attacks.             | High     |
| suicide               | Detects unprotected `selfdestruct`.             | High     |
| uninitialized\_state  | Detects state accessed with no initialization.  | High     |
| msg\_value\_loop      | Detects `msg.value` used in loop.               | Medium   |
| delegatecall\_loop    | Detects `delegatecall` used in loop.            | Medium   |
| tainted\_send         | Detects send to a user-defined address.         | Medium   |



