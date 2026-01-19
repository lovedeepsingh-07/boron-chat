{
  ctx,
  client_runtime,
  ...
}: let
  client_runtime_flags = {
    linux = "-DCLIENT_RUNTIME_LIB=${client_runtime.linux}/lib/libclient_runtime.a -DCLIENT_RUNTIME_INCLUDE_DIR=${client_runtime.linux}/include -DCLIENT_RUNTIME_SRC=${client_runtime.linux}/src/client_runtime.cpp";
    windows = "-DCLIENT_RUNTIME_LIB=${client_runtime.windows}/lib/libclient_runtime.a -DCLIENT_RUNTIME_INCLUDE_DIR=${client_runtime.windows}/include -DCLIENT_RUNTIME_SRC=${client_runtime.windows}/src/client_runtime.cpp";
  };
  windows_flags = "-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_PROCESSOR=x86_64 -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++";
in {
  windows = ctx.cross_pkgs.stdenv.mkDerivation {
    pname = "boron_client";
    version = "0.1.0";
    src = ../client;
    nativeBuildInputs = [
      ctx.pkgs.ninja
      ctx.pkgs.cmake
      ctx.pkgs.clang
      ctx.pkgs.pkg-config
    ];
    buildInputs = [
      client_runtime.windows
      ctx.cross_pkgs.windows.pthreads
    ];
    configurePhase = ''
      ${ctx.deps.setup_script}
      mkdir -p build
      cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release -DNIX_BUILD=ON ${client_runtime_flags.windows} ${windows_flags}
    '';
    buildPhase = ''
      cmake --build build
    '';
    installPhase = ''
         mkdir -p $out/bin
      cp -r assets $out/bin/
         cp -r build/boron_client.exe $out/bin/
    '';
  };
  linux = ctx.pkgs.stdenv.mkDerivation {
    pname = "boron_client";
    version = "0.1.0";
    src = ../client;
    nativeBuildInputs = [
      ctx.pkgs.ninja
      ctx.pkgs.cmake
      ctx.pkgs.clang
      ctx.pkgs.pkg-config
    ];
    buildInputs = [
      client_runtime.linux
      ctx.pkgs.libGL
      ctx.pkgs.xorg.libX11
      ctx.pkgs.libxkbcommon
      ctx.pkgs.xorg.libXrandr
      ctx.pkgs.xorg.libXinerama
      ctx.pkgs.xorg.libXcursor
      ctx.pkgs.xorg.libXi
    ];
    configurePhase = ''
      ${ctx.deps.setup_script}
      mkdir -p build
      cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release -DNIX_BUILD=ON ${client_runtime_flags.linux}
    '';
    buildPhase = ''
      cmake --build build
    '';
    installPhase = ''
         mkdir -p $out/bin
      cp -r assets $out/bin/
         cp -r build/boron_client $out/bin/
    '';
  };
}
