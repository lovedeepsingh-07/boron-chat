{
  pkgs,
  rust_platform,
  version,
  ...
}: let
  crate_toml = builtins.fromTOML (builtins.readFile ../rust/boron_server/Cargo.toml);
  package_name = crate_toml.package.name;
in
  rust_platform.buildRustPackage {
    pname = package_name;
    inherit version;
    src = ../rust;
    cargoBuildFlags = ["-p" "boron_server"];
    buildInputs = [];
    nativeBuildInputs = [pkgs.pkg-config];
    cargoLock.lockFile = ../rust/Cargo.lock;
  }
