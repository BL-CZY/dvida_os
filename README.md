<h1>Dvida OS</h1>

This is a simple operating system that I am developing based on the osdev wiki

<h1>Build</h1>

<h3>First of all</h3>
If you want to build this, you first of all need a gcc cross compiler toolchain with the target i686-elf
After building, set the following environment variables:
I686_GCC="path/to/cross-gcc"
I686_LD="path/to/cross-ld"

<h3>Secondly</h3>
On Nix-OS, you can run nix-shell at the root directory of the project, which will then have all other packages required

For non-Nix-OS, these are the packages required:<br />
nasm<br />
qemu<br />
grub2<br />
xorriso<br />
gnumake<br />