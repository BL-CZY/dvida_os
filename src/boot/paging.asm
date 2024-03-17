[bits 32]

PRESENT equ 0x1 ; otherwise not present
WRITABLE equ 0x2 ; otherwise readonly
ACCESS_TO_ALL equ 0x4 ; otherwise access to supervisor only
WRITE_THROUGH equ 0x8 ; otherwise write back
CACHE_DIABLE equ 0x10 ; otherwise it will cache
ACCESSED equ 0x20 ; otherwise not accessed
;? NOT IMPORTANT FOR 4Kib PAGES equ 0x40
FOUR_MIB_SIZE equ 0x80 ; otherwise 4Kib size ;? page directory entry only
;? NOT IMPORTANT FOR 4Kib PAGES equ 0x200

section .data

align 4096

page_directory:
    times 1024 dd PRESENT | WRITABLE ; reserve space for the page directory

; reserve space for page tables
%assign i 0
%rep 1024
align 4096

page_table_%+i:
    times 1024 dd PRESENT | WRITABLE
%assign i i + 1
%endrep

section .text

extern paging_debug_tool
global page_directory
global paging_init

paging_init:
    pushad
    %assign i 0
    %assign j 0
    %rep 1024
    mov ebx, 0
    fill_page_table_%+i:
        mov eax, ebx
        imul eax, 0x1000
        add eax, %+j
        or dword [page_table_%+i + ebx * 4], eax
        inc ebx
        cmp ebx, 1024
        jb fill_page_table_%+i
    mov eax, page_table_%+i
    or dword [page_directory + %+i * 4], eax
    %assign i i + 1
    %assign j j + 0x400000
    %endrep

    mov eax, page_directory ; load the page directory
    mov cr3, eax ; set cr3

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    popad
    ret