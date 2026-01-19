{ctx, ...}: {
  windows = ctx.rust_platform.windows.buildRustPackage {
    pname = "boron_server";
    version = "0.1.0";
    src = ../rust;
    cargoBuildFlags = ["-p" "boron_server"];
    buildInputs = [ctx.cross_pkgs.windows.pthreads];
    nativeBuildInputs = [ctx.pkgs.pkg-config];
    cargoLock.lockFile = ../rust/Cargo.lock;
  };
  linux = ctx.rust_platform.linux.buildRustPackage {
    pname = "boron_server";
    version = "0.1.0";
    src = ../rust;
    cargoBuildFlags = ["-p" "boron_server"];
    buildInputs = [];
    nativeBuildInputs = [ctx.pkgs.pkg-config];
    cargoLock.lockFile = ../rust/Cargo.lock;
  };
}
