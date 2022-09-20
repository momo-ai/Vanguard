{ stdenv, cmake, ninja,
  llvmPackages_13, lib, nodePackages, solang, python3
}:

let
  libllvm = llvmPackages_13.tools.libllvm;
in
stdenv.mkDerivation {
  name = "Vanguard";
  version = "0.0.1";
  src =
    let
      src0 = builtins.path {
        name = "libVanguard-source";
        path = ./.;
      };
    in
    lib.cleanSourceWith {
      filter = path: type: !(lib.lists.any (x: x) [
        (lib.strings.hasSuffix ".nix" (toString path))
        (type == "regular" && baseNameOf path == "flake.lock")
        (type == "directory" && lib.strings.removePrefix (toString (src0 + "/")) (toString path) == "deps")
      ]);
      src = src0;
    };

  nativeBuildInputs = [ cmake ninja python3 ];
  buildInputs = [
    libllvm
  ];

  postInstall = ''
    install -m755 -D ../run.py $out/bin/vanguard
  '';

 # outputs = [ "out" "dev" ];

  LLVM_HOME="${libllvm}";
}
