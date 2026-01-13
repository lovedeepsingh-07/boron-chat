{
  description = "boron-chat";
  inputs = {
    nixpkgs.url =
      "github:nixos/nixpkgs/d2ed99647a4b195f0bcc440f76edfa10aeb3b743";
    rust_overlay = {
      url = "github:oxalica/rust-overlay/a9c35d6e7cb70c5719170b6c2d3bb589c5e048af";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    flake-utils.url =
      "github:numtide/flake-utils/11707dc2f618dd54ca8739b309ec4fc024de578b";
  };
  outputs = { ... }@inputs:
    inputs.flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import inputs.nixpkgs {
          inherit system;
          overlays = [ ];
        };
        cross_pkgs = pkgs.pkgsCross.mingwW64;
        rust_bin = inputs.rust_overlay.lib.mkRustBin { }
          pkgs.pkgsCross.mingwW64.buildPackages;
        rust_pkg = rust_bin.stable."1.88.0".default.override {
          extensions = [ "rust-src" ];
          targets = [ "x86_64-pc-windows-gnu" ];
        };
        deps = import ./_nix/deps.nix { inherit pkgs; };
      in {
        devShells.default = import ./_nix/shell.nix { inherit pkgs cross_pkgs rust_pkg;};
		packages.server = import ./_nix/server_pkg.nix {inherit pkgs cross_pkgs rust_pkg;};
        apps.setup = inputs.flake-utils.lib.mkApp {
          drv = pkgs.writeShellApplication {
            name = "setup";
            runtimeInputs = [ ];
            text = deps.setup_script;
          };
        };
      });
}
