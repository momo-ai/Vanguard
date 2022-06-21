{
  inputs = {
    libBlockchain.url = "github:Veridise/libBlockchain/nix";
    libBlockchain.inputs.nixpkgs.follows = "nixpkgs";

    flake-utils.url = "github:numtide/flake-utils/v1.0.0";
  };

  outputs = { self, nixpkgs, libBlockchain, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ self.overlays.default ];
        };

        solc-typed-ast = pkgs.callPackage ./nix/solc-typed-ast { inherit pkgs; };
      in {

    packages = flake-utils.lib.flattenTree {
      libVanguard = pkgs.libVanguard;
      default = pkgs.libVanguard;

      # for debugging
      solang = pkgs.solang;
    };

    devShells = flake-utils.lib.flattenTree {
      runVanguard = pkgs.mkShell {
        buildInputs = [
          pkgs.libVanguard
          pkgs.llvmPackages_13.llvm
          pkgs.z3
          (pkgs.python3.withPackages (p: [
            p.pip
            p.tabulate
          ]))
          # dependencies for solidity frontend
          pkgs.nodejs
          pkgs.nodePackages.typescript
          pkgs.solang
          solc-typed-ast.solc-typed-ast

          # dependencies for rust frontend
          pkgs.rustc
          pkgs.cargo
        ];
      };
    };
  }) // {
    overlays.default = final: prev: {
      libVanguard = with final; callPackage ./libVanguard.nix {
        inherit (libBlockchain.packages.${system}) libBlockchain;
      };

      solang = with final; callPackage ./solang.nix { system = "aarch64-darwin"; };
    };
  };
}
