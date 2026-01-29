{
  pkgs,
  rust_pkg,
  deps,
  package_name,
  version,
  ...
}: let
  rust_platform = pkgs.makeRustPlatform {
    cargo = rust_pkg;
    rustc = rust_pkg;
  };
  server = import ./server.nix {inherit pkgs rust_platform version;};
  client_runtime = import ./client_runtime.nix {inherit pkgs rust_platform version;};
  client = import ./client.nix {inherit pkgs deps client_runtime version;};
in rec {
  inherit server client_runtime client;
  default = pkgs.stdenv.mkDerivation {
    name = package_name;
    dontUnpack = true;
    nativeBuildInputs = [
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
  release = pkgs.stdenv.mkDerivation {
    name = package_name;
    dontUnpack = true;
    nativeBuildInputs = [pkgs.zip];
    installPhase = ''
      mkdir -p $out/stage
      cp -r ${default}/bin/* $out/stage/
      cd $out/stage/
      zip -r $out/${package_name}-${version}-linux-x86_64.zip .
    '';
  };
}
