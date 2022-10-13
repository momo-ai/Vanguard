{ stdenv, lib, fetchFromGitHub,
  cmake, ninja,
  llvmPackages_13, z3-cmake
}:

stdenv.mkDerivation {
  pname = "svf";
  version = "2.5";
  src = fetchFromGitHub {
    owner = "SVF-tools";
    repo = "SVF";
    rev = "SVF-2.5";
    hash = "sha256-dN93k+zoVdvribfr3Fw+KYFtS+fGki5HJCUDwT+D6rE=";
  };

  patches = [
    # Fix CMake lists
    ./z3-dep.patch

    # Don't -Werror -Wall
    ./compile-flags.patch

    # Add missing include
    ./exestate.patch

    # Export CMake configuration
    ./cmake-export.patch

    # Hardcode paths in extapi
    ./extapi-path.patch
  ];

  buildInputs = [
    llvmPackages_13.libllvm
  ];

  propagatedBuildInputs = [
    # We cannot use the normal z3 from nixpkgs, because it uses the old
    # ./configure based build, which does not have pkg-config files or CMake
    # config files.
    z3-cmake
  ];

  nativeBuildInputs = [ cmake ninja ];
  hardeningDisable = [ "format" ];

  # SVF hardcodes its dependency locations in environment variables
  LLVM_DIR = "${llvmPackages_13.libllvm}/lib/cmake/LLVM";
}
