{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    { nixpkgs, flake-utils,rust-overlay, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ rust-overlay.overlays.default ];
        };
        pahcer = pkgs.callPackage ./nix/pahcer/default.nix {};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [ 
            pkgs.uv 
            pahcer
          ];
          shellHook = ''
            source .venv/bin/activate
          '';
        };
      }
    );
}
