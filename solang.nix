{ lib, stdenvNoCC, fetchurl, autoPatchelfHook

, libiconv }:

let
  versions = {
    "0.1.12" = {
      aarch64-darwin = {
        url = "https://github.com/hyperledger-labs/solang/releases/download/v0.1.12/solang-mac-arm";
        sha256 = "0f5r9666kbz9nf67h00c5my2gs51a8znzp1mcvykqp4x6qp5vgp7";
      };
    };
  };

  system = stdenvNoCC.hostPlatform.system;
in
stdenvNoCC.mkDerivation {
  name = "solang";
  version = "0.1.12";
  nativeBuildInputs =
    if stdenvNoCC.isDarwin
    then [ libiconv ]
    else [ autoPatchelfHook ];

  src = fetchurl {
    inherit (versions."0.1.12".${system}) url sha256;
  };

  dontUnpack = true;

  installPhase = ''
    mkdir -p $out/bin
    install -m755 -D $src $out/bin/solang
  '';

  doInstallCheck = true;
  installCheckPhase = ''
    $out/bin/solang --version > /dev/null
  '';
}
