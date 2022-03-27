# Vanguard
Vanguard is an open-source static analyzer for finding bugs in Smart Contracts. It provides a chain-agnostic way of
detecting common vulnerabilities in any smart contract language that can be compiled to LLVM. 

## Dependencies
 * LLVM 13
 * Z3
 * libBlockchain
 * CMake

## Build
To build, please execute the following commands. 

```bash
export LLVM_HOME=<home_llvm_dir>
export Z3_HOME=<home_z3_dir>
export LIBBLOCKCHAIN_HOME=<home_libblockchain_dir>
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```

## Usage
```bash
opt --load=build/lib/libVanguard.dylib -enable-new-pm=0 <passes> --summary=<summary> <llvm bytecode> -o /dev/null
```

### Passes
| Name          | Description                                     |
| ------------- | ----------------------------------------------- |
| intra-example | Prints out all of the functions in the bc file  |

