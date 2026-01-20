{
  pkgs,
  rust_platform,
  ...
}:
rust_platform.buildRustPackage {
  pname = "client_runtime";
  version = "0.1.0";
  src = ../rust;
  nativeBuildInputs = [pkgs.pkg-config];
  buildInputs = [];
  cargoLock.lockFile = ../rust/Cargo.lock;
  buildPhase = ''
    cargo build -p client_runtime --release
  '';
  installPhase = ''
    mkdir -p $out/lib $out/src $out/include/rust
    cp -r target/release/libclient_runtime.a $out/lib/
    cp target/cxxbridge/client_runtime/src/lib.rs.cc $out/src/client_runtime.cpp
    cp target/cxxbridge/client_runtime/src/lib.rs.h $out/include/client_runtime.h
    cp target/cxxbridge/rust/cxx.h $out/include/rust/cxx.h
  '';
  fixupPhase = "true";
}
