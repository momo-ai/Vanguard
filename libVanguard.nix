{ stdenv, cmake, ninja,
  llvmPackages_13, lib, python3, git, gtest,
  svf, lit
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
      isTopLevelDir = path: type: name:
        (type == "directory" &&
         lib.strings.removePrefix (toString (src0 + "/")) (toString path) == name);
    in
    lib.cleanSourceWith {
      filter = path: type: !(lib.lists.any (x: x) [
        (lib.strings.hasSuffix ".nix" (toString path))
        (type == "regular" && baseNameOf path == "flake.lock")
        (isTopLevelDir path type "deps")
        (isTopLevelDir path type ".github")
        (isTopLevelDir path type "nix")
      ]);
      src = src0;
    };

  nativeBuildInputs = [ cmake ninja python3 git gtest ];
  cmakeFlags = ["-DDOWNLOAD_GTEST=OFF"]; 

  buildInputs = [
    libllvm
    svf
  ];

  checkInputs = [
    lit
  ];

  postInstall = ''
    install -m755 -D ../run.py $out/bin/vanguard
  '';

  doCheck = true;

 # outputs = [ "out" "dev" ];

  LLVM_HOME="${libllvm}";
}
