{
  pkgs,
  cross_pkgs,
  deps,
  runtime_pkg,
  ...
}: let
  runtime_pkg_flags = "-DRUNTIME_LIB=${runtime_pkg}/lib/libruntime.a -DRUNTIME_INCLUDE_DIR=${runtime_pkg}/include -DRUNTIME_SRC=${runtime_pkg}/src/runtime.cpp";
  windows_flags = "-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_PROCESSOR=x86_64 -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++";
  cmake_flags = "-DCMAKE_BUILD_TYPE=Release -DNIX_BUILD=ON ${runtime_pkg_flags} ${windows_flags}";
in
  cross_pkgs.stdenv.mkDerivation {
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
      runtime_pkg
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
  }
