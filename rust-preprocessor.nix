{ stdenv, fetchFromGitHub, python3 }:

stdenv.mkDerivation {
  name = "rust-preprocessor";
  version = "0.0.1";

  buildInputs = [ python3 ];

  src = fetchFromGitHub {
    #https://github.com/Veridise/RustPreprocessor/tree/483e1537a3896434bb63a5ea39848bb3197d4f3d
    owner = "Veridise";
    repo = "RustPreprocessor";
    rev = "483e1537a3896434bb63a5ea39848bb3197d4f3d";
    sha256 = "sha256-UA0s4yv8lhVgVg1tvUCwg6ryEWrX0F7uAEEm6XHQaeg=";
  };

  installPhase = ''
  mkdir -p $out/bin
  install $src/summarizer.py $out/bin/rust-preprocessor'';

}
