{
  inputs = {


    flake-utils.url = "github:numtide/flake-utils/v1.0.0";
  };

  # Custom colored bash prompt
  nixConfig.bash-prompt = ''\[\e[0;32m\][vanguard]\[\e[m\] \[\e[38;5;244m\]\w\[\e[m\] % '';

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ self.overlays.default ];
        };
      in {

    packages = flake-utils.lib.flattenTree {
      inherit (pkgs) libVanguard solc-typed-ast;

      default = pkgs.libVanguard;

      # for debugging
      inherit (pkgs) solang solidity-preprocessor;
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
          pkgs.solc-typed-ast

          # dependencies for rust frontend
          pkgs.rustc
          pkgs.cargo
        ];
      };

      default = pkgs.libVanguard.overrideAttrs (attrs: {
        buildInputs = attrs.buildInputs ++ [
          pkgs.nodejs
          pkgs.nodePackages.npm
          pkgs.nodePackages.typescript
        ];
      });
    };
  }) // {
    overlays.default = final: prev: {
      libVanguard = with final; callPackage ./libVanguard.nix {};

      solc-typed-ast = (final.callPackage ./nix/solc-typed-ast { pkgs = final; }).solc-typed-ast;

      solang = with final; callPackage ./solang.nix {};

      solidity-preprocessor = final.callPackage ./nix/solidity-preprocessor.nix {
        pkgs = final;

        inherit (final) lib nodejs;
      };
    };
  };
}
