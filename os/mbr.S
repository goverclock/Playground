SECTION MBR vstart=0x7c00

; set all regs to 0
mov ax,cs   ; cs = 0 now
mov ds,ax
mov es,ax
mov ss,ax
mov fs,ax
mov sp,0x7c00

; clear screen
mov ax, 0x600
mov bx, 0x700
mov cx, 0
mov dx, 0x184f
int 0x10

; get cursor position
;mov ah, 3
;mov bh, 0
;int 0x10
mov cx, 0
mov dx, 0

mov ax, message
mov bp, ax
mov cx, 9
mov ax, 0x1301
mov bx, 0x2
int 0x10

jmp $

message db "FUCK THIS"
times 510-($-$$) db 0
db 0x55,0xaa
