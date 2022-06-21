{ lib, stdenv, fetchurl, autoPatchelfHook

, libiconv

# which system is being built
, system }:

let
  versions = {
    "0.1.12" = {
      aarch64-darwin = {
        url = "https://github.com/hyperledger-labs/solang/releases/download/v0.1.12/solang-mac-arm";
        sha256 = "0f5r9666kbz9nf67h00c5my2gs51a8znzp1mcvykqp4x6qp5vgp7";
      };
    };
  };

  patchPaths =
    if stdenv.isDarwin
    then ''
      install_name_tool -id solang $out/bin/solang
    ''
    else ''
    '';
in
stdenv.mkDerivation {
  name = "solang";
  version = "0.1.12";
  nativeBuildInputs =
    if stdenv.isDarwin
    then [ libiconv ]
    else [ autoPatchelfHook ];

  src = fetchurl (versions."0.1.12".${system} // {
    downloadToTemp = true;
    postFetch = ''
      install $downloadedFile $out
    '';
  });
  sourceRoot = ".";

  dontUnpack = true;
  dontConfigure = true;
  dontBuild = true;

  installPhase = ''
    install -m755 -D $src $out/bin/solang
    ${patchPaths}
  '';

  doInstallCheck = true;
  installCheck = ''
    $out/bin/solang --version > /dev/null
  '';
}
