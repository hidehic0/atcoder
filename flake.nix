{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    oj-download-atc = {
      url = "github:hidehic0/oj-download-atc";
      inputs.nixpkgs.follows = "nixpkgs";
    };

  };

  outputs =
    {
      nixpkgs,
      flake-utils,
      rust-overlay,
      oj-download-atc,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ rust-overlay.overlays.default ];
        };
        pahcer = pkgs.callPackage ./nix/pahcer/default.nix { };
        acc = pkgs.callPackage ./nix/atcoder-cli/default.nix { };
        cpp-dump = pkgs.callPackage ./nix/cpp-dump/default.nix { };
        codon = pkgs.callPackage ./nix/codon/default.nix { };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.uv
            pahcer
            acc
            pkgs.rust-bin.stable.latest.default
            oj-download-atc.packages.${system}.default
            pkgs.boost
            # pkgs.ac-library
            # cpp-dump
            pkgs.zig
            codon
            pkgs.pkg-config
            pkgs.zlib
            pkgs.unordered_dense
          ];
          shellHook = ''
            source .venv/bin/activate
            export ZIG_GLOBAL_CACHE_DIR=/tmp
          '';
        };
      }
    );
}
