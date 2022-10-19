#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SVF_INSTALL_DIR=${SCRIPT_DIR}/../deps/SVF/

# Download SVF
git clone https://github.com/SVF-tools/SVF.git ${SCRIPT_DIR}/SVF
cd ${SCRIPT_DIR}/SVF

#Check out v 2.5
git checkout SVF-2.5

for f in `ls ${SCRIPT_DIR}/../nix/svf/*.patch`
do
    echo "Applying patch $f"
    git apply $f
done

# TODO: Add option to for Debug build.
rm -rf ./'Release-build'
mkdir ./'Release-build'
cd ./'Release-build'
cmake -D CMAKE_INSTALL_PREFIX:PATH=${SVF_INSTALL_DIR} ../
# TODO: Add option for job num
make -j 8
make install

cd ${SCRIPT_DIR}
rm -rf ${SCRIPT_DIR}/SVF
