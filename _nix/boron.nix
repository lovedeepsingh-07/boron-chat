{
  ctx,
  boron_server,
  boron_client,
  ...
}: {
  windows = ctx.cross_pkgs.stdenv.mkDerivation {
    name = "boron";
    dontUnpack = true;
    buildInputs = [
      boron_server.windows
      boron_client.windows
    ];
    installPhase = ''
         mkdir -p $out/bin
      cp -r ${boron_server.windows}/bin/boron_server* $out/bin/
      cp -r ${boron_client.windows}/bin/boron_client* $out/bin/
      cp -r ${boron_client.windows}/bin/assets $out/bin/
    '';
  };
  linux = ctx.pkgs.stdenv.mkDerivation {
    name = "boron";
    dontUnpack = true;
    buildInputs = [
      boron_server.linux
      boron_client.linux
    ];
    installPhase = ''
         mkdir -p $out/bin
      cp -r ${boron_server.linux}/bin/boron_server* $out/bin/
      cp -r ${boron_client.linux}/bin/boron_client* $out/bin/
      cp -r ${boron_client.linux}/bin/assets $out/bin/
    '';
  };
}
