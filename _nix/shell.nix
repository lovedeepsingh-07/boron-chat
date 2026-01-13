{
  pkgs,
  cross_pkgs,
  rust_pkg,
  ...
}: {
  windows = cross_pkgs.mkShell {
    nativeBuildInputs = [pkgs.ninja pkgs.cmake rust_pkg pkgs.pkg-config pkgs.alejandra];
    buildInputs = [cross_pkgs.windows.pthreads];
    shellHook = "zsh";
  };
}
