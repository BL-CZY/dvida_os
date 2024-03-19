{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [ 
	    pkgs.nasm
	    pkgs.qemu
	    pkgs.grub2
	    pkgs.xorriso
      pkgs.gnumake
	    pkgs.dhex
      pkgs.cloc
      pkgsCross.i686-embedded.buildPackages.gcc
      pkgsCross.i686-embedded.buildPackages.libgcc
      pkgsCross.i686-embedded.buildPackages.binutils
    ];
    
    shellHook = ''
      export I686_GCC=i686-elf-gcc
      export I686_LD=i686-elf-ld
    '';
}