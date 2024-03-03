[org 0x7c00]
[bits 16]

; FAT 12 header
jmp start
nop

bdb_oem:                    db 'MSWIN4.1'           ; 8 bytes
bdb_bytes_per_sector:       dw 512
bdb_sectors_per_cluster:    db 1
bdb_reserved_sectors:       dw 1
bdb_fat_count:              db 2
bdb_dir_entries_count:      dw 0E0h
bdb_total_sectors:          dw 2880                 ; 2880 * 512 = 1.44MB
bdb_media_descriptor_type:  db 0F0h                 ; F0 = 3.5" floppy disk
bdb_sectors_per_fat:        dw 9                    ; 9 sectors/fat
bdb_sectors_per_track:      dw 18
bdb_heads:                  dw 2
bdb_hidden_sectors:         dd 0
bdb_large_sector_count:     dd 0

; extended boot record
ebr_drive_number:           db 0                    ; 0x00 floppy, 0x80 hdd, useless
                            db 0                    ; reserved
ebr_signature:              db 29h
ebr_volume_id:              db 12h, 34h, 56h, 78h   ; serial number, value doesn't matter
ebr_volume_label:           db 'DVIDA_OS   '        ; 11 bytes, padded with spaces
ebr_system_id:              db 'FAT12   '           ; 8 bytes

VGA_WIDTH equ 80
VGA_HEIGHT equ 25

i686_gdt_start: ; label for the start of the gdt

    i686_null_descriptor: 
        .limit_low: dw 0x00
        .base_low: dw 0x00
        .base_middle: db 0x00
        .access: db 0x00
        .granularity: db 0x00
        .base_high: db 0x00

    i686_kernel_code_descriptor:
        .limit_low: dw 0xFFFF
        .base_low: dw 0x00
        .base_middle: db 0x00
        .access: db 0x9A
        .granularity: db 0xCF
        .base_high: db 0x00

    i686_kernel_data_descriptor:
        .limit_low: dw 0xFFFF
        .base_low: dw 0x00
        .base_middle: db 0x00
        .access: db 0x92
        .granularity: db 0xCF
        .base_high: db 0x00

    i686_user_code_descriptor:
        .limit_low: dw 0xFFFF
        .base_low: dw 0x00
        .base_middle: db 0x00
        .access: db 0xFA
        .granularity: db 0xCF
        .base_high: db 0x00

    i686_user_data_descriptor:
        .limit_low: dw 0xFFFF
        .base_low: dw 0x00
        .base_middle: db 0x00
        .access: db 0xF2
        .granularity: db 0xCF
        .base_high: db 0x00

i686_gdt_end: ; label for the end of the gdt

clear_screen:

    mov ax, 0xB800 ; 0xB8000 is too big, so segmentation is needed
    mov ds, ax ; set ds
    mov es, ax ; set es
    mov cx, 0 ; cx would be height
    mov bx, 0 ; bx would be width

    .loop_height:

        .loop_width:
            mov di, cx ; move cx to di
            imul di, VGA_WIDTH ; multiply di by the width
            add di, bx ; add bx to di to get the position
            imul di, 2
            mov word [es:di], 0x0F00 ; set the offset
            inc bx ; add bx
            cmp bx, VGA_WIDTH ; compare bx and width
            jne .loop_width ; repeat until finishes

        mov bx, 0 ; reset bx
        inc cx ; add the row number
        cmp cx, VGA_HEIGHT ; compare the row number and the height
        jne .loop_height ; if not equal then do so

    xor ax, ax ; set ax to 0
    mov ds, ax ; reset ds
    mov es, ax ; reset es
    mov cx, 0 ; reset cx
    mov ax, 0 ; reset ax
    mov bx, 0 ; reset bx

    ret

start:    
    call clear_screen

times 510-($-$$) db 0
db 0x55, 0xAA
