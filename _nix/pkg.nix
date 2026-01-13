{
  cross_pkgs,
  server_pkg,
  client_pkg,
  ...
}:
cross_pkgs.stdenv.mkDerivation {
  name = "boron";
  dontUnpack = true;
  buildInputs = [
    server_pkg
    client_pkg
  ];
  installPhase = ''
       mkdir -p $out/bin
    cp -r ${server_pkg}/bin/boron_server* $out/bin/
    cp -r ${client_pkg}/bin/boron_client* $out/bin/
    cp -r ${client_pkg}/bin/assets $out/bin/
  '';
}
