{
  description = "Description for the project";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [];
      systems = [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" "x86_64-darwin" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
# Per-system attributes can be defined here. The self' and inputs'
        # module parameters provide easy access to attributes of the same
        # system.

        packages.default = config.packages.CppMermaidGen;
        packages.CppMermaidGen = pkgs.callPackage ./default.nix { };

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # C++ Compiler is already part of stdenv
            cmake
          ];
        };
              };
      };
}
