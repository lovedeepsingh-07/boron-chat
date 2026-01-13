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
    pname = "runtime";
    version = "0.1.0";
    src = ../boron_rust;
    nativeBuildInputs = [pkgs.pkg-config];
    buildInputs = [cross_pkgs.windows.pthreads];
    cargoLock.lockFile = ../boron_rust/Cargo.lock;
    buildPhase = ''
      cargo build -p runtime --release --target x86_64-pc-windows-gnu
    '';
    installPhase = ''
      mkdir -p $out/lib $out/src $out/include/rust
      cp -r target/x86_64-pc-windows-gnu/release/libruntime.a $out/lib/
      cp target/x86_64-pc-windows-gnu/cxxbridge/runtime/src/lib.rs.cc $out/src/runtime.cpp
      cp target/x86_64-pc-windows-gnu/cxxbridge/runtime/src/lib.rs.h $out/include/runtime.h
      cp target/x86_64-pc-windows-gnu/cxxbridge/rust/cxx.h $out/include/rust/cxx.h
    '';
    fixupPhase = "true";
  }
