{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [ 
	    pkgs.nasm
	    pkgs.qemu
	    pkgs.grub2
	    pkgs.xorriso
	    pkgs.hexcurse
	    pkgs.dhex
      pkgs.rustc
      pkgs.gtk3
    ];
    
    shellHook = ''
      export I686_GCC="$HOME/opt/cross-i686/bin/i686-elf-gcc"
      export I686_LD="$HOME/opt/cross-i686/bin/i686-elf-ld"
    '';
}
