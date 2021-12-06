[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov bx, LOADING
call print
call print_nl

; load kernel
mov bx, KERNEL_OFFSET
mov dh, 8
mov dl, [BOOT_DRIVE]
call disk_load

call switch_to_pm
jmp $

%include "bootloader/textio.asm"
%include "bootloader/diskio.asm"
%include "bootloader/gdt.asm"
%include "bootloader/to-protected-mode.asm"
%include "bootloader/32bit-textio.asm"

[bits 32]
BEGIN_PM:
  mov ebx, PROT_MODE
  call print_string_pm
  call KERNEL_OFFSET
  jmp $

BOOT_DRIVE db 0
LOADING db "Entering protected mode", 0
PROT_MODE db "Entered protected mode!", 0

times 510-($-$$) db 0
dw 0xaa55
