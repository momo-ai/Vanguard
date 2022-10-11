# Copied from https://github.com/NixOS/nixpkgs/pull/147853/files
# Z3 built with CMake

{ lib
, stdenv
, cmake
, ninja
, fetchFromGitHub
, python3
, fixDarwinDylibNames
, javaBindings ? false
, pythonBindings ? true
, jdk ? null
, ocaml ? null
, findlib ? null
, zarith ? null
}:

assert javaBindings -> jdk != null;

with lib;

stdenv.mkDerivation rec {
  pname = "z3";
  version = "4.11.0";

  src = fetchFromGitHub {
    owner = "Z3Prover";
    repo = pname;
    rev = "z3-${version}";
    sha256 = "sha256-ItmtZHDhCeLAVtN7K80dqyAh20o7TM4xk2sTb9QgHvk=";
  };

  nativeBuildInputs = optional stdenv.hostPlatform.isDarwin fixDarwinDylibNames;
  buildInputs = [ cmake ninja ]
    ++ optional javaBindings jdk
  ;
  propagatedBuildInputs = [ python3.pkgs.setuptools ];
  enableParallelBuilding = true;

  cmakeFlags = lib.optionals javaBindings [
    "-DZ3_BUILD_JAVA_BINDINGS=True"
    "-DZ3_INSTALL_JAVA_BINDINGS=True"
  ];

  outputs = [ "out" "lib" "dev" ];

  meta = with lib; {
    description = "A high-performance theorem prover and SMT solver";
    homepage = "https://github.com/Z3Prover/z3";
    license = licenses.mit;
    platforms = platforms.unix;
    maintainers = with maintainers; [ thoughtpolice ttuegel ];
  };
}

