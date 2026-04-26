{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  packages = with pkgs; [
    clang-tools
    gdb
    codespell
    cppcheck
    pkg-config
    cmake
    glfw
    glm
    libGL
    libxkbcommon
  ];

  shellHook = "export GLFW_WAYLAND=1";
}
