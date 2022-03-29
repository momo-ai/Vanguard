for file in test/reentrancy_tests/*
do
  if [[ -f $file ]]; then
	  echo $file
	  /opt/homebrew/Cellar/llvm/13.0.1_1/bin/opt --load=cmake-build-debug/lib/libVanguard.dylib -enable-new-pm=0 --reentrancy $file -o /dev/null
  fi
done