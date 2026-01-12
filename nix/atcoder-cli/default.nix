{
  lib,
  fetchFromGitHub,
  buildNpmPackage,
  ...
}:
let
  version = "8a7222c";
in
buildNpmPackage {
  pname = "atcoder-cli";
  inherit version;
  src = fetchFromGitHub {
    owner = "hidehic0";
    repo = "atcoder-cli";
    rev = "8a7222c0d760f75e995c0d62671b859f8b796e06";
    hash = "sha256-4dXyI/utDEAsi1xpcqUSr4ivo/XbhaXXOmO9jT8CRhA=";
  };
  npmDepsHash = "sha256-Ab9fzqtzIuC6xfM0BBMlBu371f9QYJ0VWdoyGTLIMR0=";
  npmPackFlags = [ "--ignore-scripts" ];

  NODE_OPTIONS = "--openssl-legacy-provider";
  meta = {
    description = "AtCoder command line tools";
    license = lib.licenses.bsd3;
  };
}
