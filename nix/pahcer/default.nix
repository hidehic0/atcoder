{
  lib,
  rustPlatform,
  fetchFromGitHub,
  ...
}:
let
  version = "0.4.0";
in
rustPlatform.buildRustPackage {
  pname = "pahcer";
  version = "v${version}";
  src = fetchFromGitHub {
    owner = "terry-u16";
    repo = "pahcer";
    tag = "v${version}";
    hash = "sha256-y+BPwiqCSRavk7QtatDGzEtyDbfvx8fZ97ABtLWoyv0=";
  };
  cargoHash = "sha256-cuGm0LbxXfnyGUCWREVwg6PznaIIXgKaH0uxKYjp3XI=";
  meta = {
    description = "A tool to run tests for AtCoder Heuristic Contest (AHC)";
    homepage = "https://github.com/terry-u16/pahcer";
    license = with lib.licenses; [
      mit
      asl20
    ];
  };
}
