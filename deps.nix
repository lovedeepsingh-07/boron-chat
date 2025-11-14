{ pkgs, ... }:
let
  fmt = pkgs.fetchFromGitHub {
    owner = "fmtlib";
    repo = "fmt";
    rev = "407c905e45ad75fc29bf0f9bb7c5c2fd3475976f";
    sha256 = "sha256-ZmI1Dv0ZabPlxa02OpERI47jp7zFfjpeWCy1WyuPYZ0=";
  };
  flecs = pkgs.fetchFromGitHub {
    owner = "SanderMertens";
    repo = "flecs";
    rev = "fc3b8999905e05b5ebb6562324c8b198d175804a";
    sha256 = "sha256-YC5SvxNP2gFq/tm9YLmCIdDQ1geA4co/l1tteQGPvhU=";
  };
  enet = pkgs.fetchFromGitHub {
    owner = "lsalzman";
    repo = "enet";
    rev = "8be2368a8001f28db44e81d5939de5e613025023";
    sha256 = "sha256-YaXdgZIIk1kfDTriKmnEBxRp8yxub3OYfvF0WJl52Ws=";
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
  imgui = pkgs.fetchFromGitHub {
    owner = "ocornut";
    repo = "imgui";
    rev = "5d4126876bc10396d4c6511853ff10964414c776";
    sha256 = "sha256-m5h/H8k/CZ5Qwr3L9+Elt8XT/Tgwr3s4HuhVtI4wkwE=";
  };
  rlimgui = pkgs.fetchFromGitHub {
    owner = "raylib-extras";
    repo = "rlImGui";
    rev = "0105acf1bfba22e883688e5b9ffb1af0536739e2";
    sha256 = "sha256-7KtzWla0kKurEzfdlYcxep0v8ZpVNRc6ELFabCQBZbU=";
  };
in
{
  setup_script = ''
    mkdir -p deps
    cp -r ${fmt} deps/fmt
    cp -r ${flecs} deps/flecs
    cp -r ${raylib} deps/raylib
    mkdir -p deps/clay
    cp -r ${clay} deps/clay/clay
    cp -r ${enet} deps/enet
    cp -r ${flatbuffers} deps/flatbuffers
    cp -r ${imgui} deps/imgui
    cp -r ${rlimgui} deps/rlimgui
  '';
}
