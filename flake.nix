{
  description = "boron-chat";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/d2ed99647a4b195f0bcc440f76edfa10aeb3b743";
    rust_overlay = {
      url = "github:oxalica/rust-overlay/a9c35d6e7cb70c5719170b6c2d3bb589c5e048af";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nixgl = {
      url = "github:nix-community/nixGL/b6105297e6f0cd041670c3e8628394d4ee247ed5";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    flake-utils.url = "github:numtide/flake-utils/11707dc2f618dd54ca8739b309ec4fc024de578b";
  };
  outputs = {...} @ inputs:
    inputs.flake-utils.lib.eachDefaultSystem (system: let
      ctx = rec {
        pkgs = import inputs.nixpkgs {
          inherit system;
          overlays = [inputs.nixgl.overlay];
        };
        cross_pkgs = pkgs.pkgsCross.mingwW64;
        rust_pkg = (inputs.rust_overlay.lib.mkRustBin {}
          cross_pkgs.buildPackages).stable."1.88.0".default.override {
          extensions = ["rust-src"];
          targets = ["x86_64-pc-windows-gnu"];
        };
        rust_platform = {
          linux = pkgs.makeRustPlatform {
            cargo = rust_pkg;
            rustc = rust_pkg;
          };
          windows = cross_pkgs.makeRustPlatform {
            cargo = rust_pkg;
            rustc = rust_pkg;
          };
        };
        deps = import ./_nix/deps.nix {inherit pkgs;};
      };
      shell = import ./_nix/shell.nix {inherit ctx;};
      boron_server = import ./_nix/boron_server.nix {inherit ctx;};
      client_runtime = import ./_nix/client_runtime.nix {inherit ctx;};
      boron_client = import ./_nix/boron_client.nix {
        inherit ctx client_runtime;
      };
      boron = import ./_nix/boron.nix {
        inherit ctx boron_server boron_client;
      };
    in {
      devShells = shell;

      packages.server-windows = boron_server.windows;
      packages.client_runtime-windows = client_runtime.windows;
      packages.client-windows = boron_client.windows;
      packages.windows = boron.windows;

      packages.server-linux = boron_server.linux;
      packages.client_runtime-linux = client_runtime.linux;
      packages.client-linux = boron_client.linux;
      packages.linux = boron.linux;

      apps.setup = inputs.flake-utils.lib.mkApp {
        drv = ctx.pkgs.writeShellApplication {
          name = "setup";
          runtimeInputs = [];
          text = ctx.deps.setup_script;
        };
      };
    });
}
