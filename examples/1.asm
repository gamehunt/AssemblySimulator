_start:
mov rax, 1
mov rbx, 10
loop:
dec rbx
cmp rbx, 0
int 0x80
jne loop