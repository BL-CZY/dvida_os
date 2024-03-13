{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [ 
	nasm
	qemu
	grub2
	xorriso
	hexcurse
	pkgs.dhex
    ];
}
