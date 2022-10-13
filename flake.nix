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
      inherit (pkgs) libVanguard solc-typed-ast svf z3-cmake;

      default = pkgs.libVanguard;

      # for debugging
      inherit (pkgs) solang solidity-preprocessor rust-preprocessor;
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
          pkgs.solidity-preprocessor
          pkgs.solang
          pkgs.python3Packages.venvShellHook
        ];
        nativeBuildInputs = (attrs.nativeBuildInputs or []) ++ [
          # clang-format, clang-tidy
          pkgs.clang-tools

          # git-clang-format
          pkgs.llvmPackages_latest.libclang.python
        ];

        cmakeBuildType = "Debug";
        cmakeFlags = ["-DCMAKE_EXPORT_COMPILE_COMMANDS=on"];

        # Don't inject security hardening & optimization flags for the debug build.
        # See: https://github.com/NixOS/nixpkgs/issues/18995
        hardeningDisable = ["all"];

        venvDir = "./.venv";
        postVenvCreation = ''
          pip3 install --upgrade pip
          # TODO: create a pyproject.toml
          pip3 install 'tabulate==0.9.0'
          # developer stuff
          pip3 install mypy black isort 'python-lsp-server[all]' pytest
        '';

        shellHook = ''
          # Fix CMAKE_COMPILE_COMMANDS
          export CXXFLAGS="$NIX_CFLAGS_COMPILE"

          # Add Vanguard binaries to PATH
          export PATH="$PWD"/build/lib:"$PATH"
        '';
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

      rust-preprocessor = final.callPackage ./rust-preprocessor.nix {};

      svf = with final; callPackage ./nix/svf/default.nix {};
      z3-cmake = with final; callPackage ./nix/z3-cmake.nix {};
    };
  };
}
