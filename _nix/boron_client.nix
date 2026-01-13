{
  pkgs,
  cross_pkgs,
  deps,
  client_runtime,
  ...
}: let
  client_runtime_flags = "-DRUNTIME_LIB=${client_runtime.windows}/lib/libruntime.a -DRUNTIME_INCLUDE_DIR=${client_runtime.windows}/include -DRUNTIME_SRC=${client_runtime.windows}/src/runtime.cpp";
  windows_flags = "-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_PROCESSOR=x86_64 -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++";
  cmake_flags = "-DCMAKE_BUILD_TYPE=Release -DNIX_BUILD=ON ${client_runtime_flags} ${windows_flags}";
in {
  windows = cross_pkgs.stdenv.mkDerivation {
    pname = "boron_client";
    version = "0.1.0";
    src = ../client;
    nativeBuildInputs = [
      pkgs.cmake
      pkgs.pkg-config
      pkgs.clang
      pkgs.ninja
    ];
    buildInputs = [
      client_runtime.windows
      cross_pkgs.windows.pthreads
    ];
    configurePhase = ''
      ${deps.setup_script}
      mkdir -p build
      cmake -G Ninja -S . -B build ${cmake_flags}
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
}
