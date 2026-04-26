{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  packages = with pkgs; [
    clang-tools
    codespell
    cppcheck
    pkg-config
    cmake
    glfw
    libGL
    libxkbcommon
  ];

  shellHook = "export GLFW_WAYLAND=1";
}
