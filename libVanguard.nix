{ stdenv, cmake, ninja,
  llvmPackages_13, libBlockchain
}:

let
  libllvm = llvmPackages_13.tools.libllvm;
in
stdenv.mkDerivation {
  name = "Vanguard";
  version = "0.0.1";
  nativeBuildInputs = [ cmake ninja ];
  src = ./.;
  buildInputs = [
    libllvm
    libBlockchain
  ];

  postInstall = ''
    install -m755 -D ../run.py $out/bin/vanguard
  '';

  outputs = [ "out" "dev" ];
  # Set include dir to out to avoid CMake issues when using nix develop
  outputInclude = "out";
  # TODO: fixup the installed cmake package config file

  LLVM_HOME="${libllvm}";
  LIBBLOCKCHAIN_HOME="${libBlockchain}";
}
