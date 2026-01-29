{
  pkgs,
  rust_pkg,
  ...
}: {
  default = pkgs.mkShell {
    nativeBuildInputs = [
      pkgs.ninja
      pkgs.cmake
      pkgs.clang
      rust_pkg
      pkgs.pkg-config
      pkgs.alejandra
      pkgs.flatbuffers
    ];
    buildInputs = [
      pkgs.nixgl.nixGLIntel
      pkgs.libGL
      pkgs.xorg.libX11
      pkgs.libxkbcommon
      pkgs.xorg.libXrandr
      pkgs.xorg.libXinerama
      pkgs.xorg.libXcursor
      pkgs.xorg.libXi
    ];
    LIBCLANG_PATH = "${pkgs.libclang.lib}/lib";
    LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath [
      pkgs.xorg.libX11
      pkgs.libxkbcommon
      pkgs.xorg.libXi
    ]}:$LD_LIBRARY_PATH";
    shellHook = "zsh";
  };
}
