; Example file #1
; Default placeholder file for AssemblySimulator
; Outputs number 1 - 9 into the console

_start:
mov rax, 1
mov rbx, 10
loop:
dec rbx
cmp rbx, 0
int 0x80
jne loop
