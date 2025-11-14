{
  description = "game";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/d2ed99647a4b195f0bcc440f76edfa10aeb3b743";
    flake-utils.url = "github:numtide/flake-utils/11707dc2f618dd54ca8739b309ec4fc024de578b";
  };
  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; overlays = []; };
        cross-pkgs = pkgs.pkgsCross.mingwW64;
        deps = import ./deps.nix { inherit pkgs; };
      in
      {
        formatter = pkgs.nixfmt-classic;
        devShells.default = cross-pkgs.mkShell {
          nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config pkgs.flatbuffers ];
          buildInputs = [ cross-pkgs.windows.pthreads ];
        };
        apps.setup = flake-utils.lib.mkApp {
          drv = pkgs.writeShellApplication {
            name = "setup";
            runtimeInputs = [ ];
            text = deps.setup_script;
          };
        };
      });
}
