<h1>Dvida OS</h1>

This is a simple operating system that I am developing based on the osdev wiki

<h1>Build</h1>

<h3>First of all</h3>
If you want to build this, you first of all need a gcc cross compiler toolchain with the target i686-elf<br />
After building, set the following environment variables:<br />
I686_GCC="path/to/cross-gcc"<br />
I686_LD="path/to/cross-ld"<br />

<h3>Secondly</h3>
On Nix-OS, you can run nix-shell at the root directory of the project, which will then have all other packages required
I am looking into the feasibility of making the cross compiler into the shell.nix

For non-Nix-OS, these are the packages required:<br />
nasm<br />
qemu<br />
grub2<br />
xorriso<br />
gnumake<br />

<h1>Run</h1>
<h3><font color="red">DO NOT RUN THIS IN A REAL MACHINE!!! THE IMMATURITY OF THIS PROJECT MIGHT ERASE YOUR DISK!!!</font></h3>
To run, a 4Gib raw disk image must be created<br />
You can use qemu-img to do so<br />
Then, simply run ./run would emulate the iso in qemu
