{ pkgs, nodejs, lib }:

# NOTE: solidity-preprocessor uses solc-typed-ast, which downloads solc
# on-demand. By default, this location is the node_modules folder -- which
# is immutable when put into the nix stoer.

# When running, must set SOLC_AST_COMPILER_CACHE variable to point outside of
# the nix store.

let
  nodePkgEnv = pkgs.callPackage ./solidity-preprocessor-nix/default.nix {
    inherit pkgs nodejs;
    inherit (pkgs.stdenv.hostPlatform) system;
  };
  src =
    let
      src0 = builtins.path {
        name = "solidity-preprocessor-source";
        path = ../deps/SolidityPreprocessor;
      };
      srcRoot = toString (src0 + "/");
    in
    lib.cleanSourceWith {
      filter = path: type: !(
        ((lib.removePrefix srcRoot (toString path)) == "dist") ||
        ((lib.removePrefix srcRoot (toString path)) == "node_modules")
      );
      src = ../deps/SolidityPreprocessor;
    };
in
nodePkgEnv.package.overrideAttrs (attrs: {
  # Don't use the default src, since it doesn't filter out dist and node_modules.
  src = src;

  buildInputs = (attrs.buildInputs or []) ++ [pkgs.nodePackages.typescript];

  postInstall = attrs.postInstall or "" + ''
    # For some reason, node2nix doesn't generate the bin folder.
    # https://github.com/svanderburg/node2nix/issues/293

    # So just add the scripts to PATH manually.
    mkdir -p "$out"/bin
    ln -s "$out"/lib/node_modules/soliditypreprocessor/dist/preprocessor.js "$out"/bin/solidity-preprocessor
    ln -s "$out"/lib/node_modules/soliditypreprocessor/dist/summarizer.js "$out"/bin/solidity-summarizer
    chmod +x "$out"/bin/solidity-preprocessor "$out"/bin/solidity-summarizer
  '';

  passthru = {
    # For debugging / introspection
    node2nixEnv = nodePkgEnv;
  };
})
