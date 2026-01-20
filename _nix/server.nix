{
  pkgs,
  rust_platform,
  ...
}:
rust_platform.buildRustPackage {
  pname = "boron_server";
  version = "0.1.0";
  src = ../rust;
  cargoBuildFlags = ["-p" "boron_server"];
  buildInputs = [];
  nativeBuildInputs = [pkgs.pkg-config];
  cargoLock.lockFile = ../rust/Cargo.lock;
}
