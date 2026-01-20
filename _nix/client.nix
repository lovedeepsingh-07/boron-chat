{
  pkgs,
  deps,
  client_runtime,
  ...
}: let
  client_runtime_flags = "-DCLIENT_RUNTIME_LIB=${client_runtime}/lib/libclient_runtime.a -DCLIENT_RUNTIME_INCLUDE_DIR=${client_runtime}/include -DCLIENT_RUNTIME_SRC=${client_runtime}/src/client_runtime.cpp";
in
  pkgs.stdenv.mkDerivation {
    pname = "boron_client";
    version = "0.1.0";
    src = ../client;
    nativeBuildInputs = [
      pkgs.ninja
      pkgs.cmake
      pkgs.clang
      pkgs.pkg-config
    ];
    buildInputs = [
      client_runtime
      pkgs.libGL
      pkgs.xorg.libX11
      pkgs.libxkbcommon
      pkgs.xorg.libXrandr
      pkgs.xorg.libXinerama
      pkgs.xorg.libXcursor
      pkgs.xorg.libXi
    ];
    configurePhase = ''
      ${deps.setup_script}
      mkdir -p build
      cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release -DNIX_BUILD=ON ${client_runtime_flags}
    '';
    buildPhase = ''
      cmake --build build
    '';
    installPhase = ''
         mkdir -p $out/bin
      cp -r assets $out/bin/
         cp -r build/boron_client $out/bin/
    '';
  }
