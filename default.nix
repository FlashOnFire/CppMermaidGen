{ pkgs ? import <nixpkgs> {} }:


# Nix derivation for basic C++ project using clang
with pkgs; clangStdenv.mkDerivation {
  name = "CppMermaidGen";
  src = ./.;

  buildInputs = [
    clang
    cmake
  ];

  installPhase = ''
    mkdir -p $out/bin
    mv CppMermaidGen $out/bin/CppMermaidGen
  '';
}
