{ctx, ...}: let
  native_build_inputs = [
    ctx.pkgs.ninja
    ctx.pkgs.cmake
    ctx.pkgs.clang
    ctx.rust_pkg
    ctx.pkgs.pkg-config
    ctx.pkgs.alejandra
    ctx.pkgs.flatbuffers
  ];
in {
  windows = ctx.cross_pkgs.mkShell {
    nativeBuildInputs = native_build_inputs;
    buildInputs = [ctx.cross_pkgs.windows.pthreads];
    DEV_PLATFORM = "WINDOWS";
    shellHook = "zsh";
  };
  linux = ctx.pkgs.mkShell {
    nativeBuildInputs = native_build_inputs;
    buildInputs = [
      ctx.pkgs.nixgl.nixGLIntel
      ctx.pkgs.libGL
      ctx.pkgs.xorg.libX11
      ctx.pkgs.libxkbcommon
      ctx.pkgs.xorg.libXrandr
      ctx.pkgs.xorg.libXinerama
      ctx.pkgs.xorg.libXcursor
      ctx.pkgs.xorg.libXi
    ];
    LIBCLANG_PATH = "${ctx.pkgs.libclang.lib}/lib";
    LD_LIBRARY_PATH = "${ctx.pkgs.lib.makeLibraryPath [
      ctx.pkgs.xorg.libX11
      ctx.pkgs.libxkbcommon
      ctx.pkgs.xorg.libXi
    ]}:$LD_LIBRARY_PATH";
    DEV_PLATFORM = "LINUX";
    shellHook = "zsh";
  };
}
