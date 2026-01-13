{
  pkgs,
  cross_pkgs,
  rust_pkg,
  ...
}: let
  rust-platform = cross_pkgs.makeRustPlatform {
    cargo = rust_pkg;
    rustc = rust_pkg;
  };
in
  rust-platform.buildRustPackage {
    pname = "boron-server";
    version = "0.1.0";
    src = ../server;
    buildInputs = [cross_pkgs.windows.pthreads];
    nativeBuildInputs = [pkgs.pkg-config];
    cargoLock.lockFile = ../server/Cargo.lock;
  }
