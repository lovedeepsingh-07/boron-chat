{
  pkgs,
  rust_pkg,
  deps,
  ...
}: let
  rust_platform = pkgs.makeRustPlatform {
    cargo = rust_pkg;
    rustc = rust_pkg;
  };
  server = import ./server.nix {inherit pkgs rust_platform;};
  client_runtime = import ./client_runtime.nix {inherit pkgs rust_platform;};
  client = import ./client.nix {inherit pkgs deps client_runtime;};
in {
  inherit server client_runtime client;
  default = pkgs.stdenv.mkDerivation {
    name = "boron";
    dontUnpack = true;
    buildInputs = [
      client
      server
    ];
    installPhase = ''
      mkdir -p $out/bin
      cp -r ${server}/bin/boron_server* $out/bin/
      cp -r ${client}/bin/boron_client* $out/bin/
      cp -r ${client}/bin/assets $out/bin/
    '';
  };
}
