{ stdenv, cmake, ninja,
  llvmPackages_13, lib, nodePackages 
}:

let
  libllvm = llvmPackages_13.tools.libllvm;
in
stdenv.mkDerivation {
  name = "Vanguard";
  version = "0.0.1";
  nativeBuildInputs = [ cmake ninja ];
  src = ./.; #lib.cleanSource
  buildInputs = [
    libllvm
    nodePackages.typescript 
  ];

  postInstall = ''
    install -m755 -D ../run.py $out/bin/vanguard
  '';

 # outputs = [ "out" "dev" ];

  LLVM_HOME="${libllvm}";
}
