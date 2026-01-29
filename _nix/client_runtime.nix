{
  pkgs,
  rust_platform,
  version,
  ...
}: let
  crate_toml = builtins.fromTOML (builtins.readFile ../rust/client_runtime/Cargo.toml);
  package_name = crate_toml.package.name;
in
  rust_platform.buildRustPackage {
    pname = package_name;
    inherit version;
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
