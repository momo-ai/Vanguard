#!/usr/bin/env bash

# copy readonly source files to read/write location (needed for Rust preprocessor)
cp -r /vanguard/toolbox_src /vanguard/tmp

# run vanguard on all source files
for f in $(find /vanguard/tmp -type f -name '*.sol' -or -name '*.rs'); do
    python3 /vanguard/run.py --src_path "$f" --detector all
done
