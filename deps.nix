{ pkgs, ... }:
let
  fmt = pkgs.fetchFromGitHub {
    owner = "fmtlib";
    repo = "fmt";
    rev = "407c905e45ad75fc29bf0f9bb7c5c2fd3475976f";
    sha256 = "sha256-ZmI1Dv0ZabPlxa02OpERI47jp7zFfjpeWCy1WyuPYZ0=";
  };
  flatbuffers = pkgs.fetchFromGitHub {
    owner = "google";
    repo = "flatbuffers";
    rev = "1c514626e83c20fffa8557e75641848e1e15cd5e";
    sha256 = "sha256-u5AVjbep3iWwGNXLrkPJUnF8SbmIXlHOYoy3NIlUl/E=";
  };
  raylib = pkgs.fetchFromGitHub {
    owner = "raysan5";
    repo = "raylib";
    rev = "1c3f9fa135cafa494af760c4cd0541c9a23cdf60";
    sha256 = "sha256-bJzuF/5UFIHewQFyCDDPrkh6eyEUv4AYAzmkkV/WjjI=";
  };
  clay = pkgs.fetchFromGitHub {
    owner = "nicbarker";
    repo = "clay";
    rev = "b25a31c1a152915cd7dd6796e6592273e5a10aac";
    sha256 = "sha256-6h1aQXqwzPc4oPuid3RfV7W0WzQFUiddjW7OtkKM0P8=";
  };
in
{
  setup_script = ''
    mkdir -p deps
    cp -r ${fmt} deps/fmt
    cp -r ${raylib} deps/raylib
    mkdir -p deps/clay
    cp -r ${clay} deps/clay/clay
    cp -r ${flatbuffers} deps/flatbuffers
  '';
}
