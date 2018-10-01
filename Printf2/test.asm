section.data

number db "AB902$"

section.text 
	global _start
_start:

	mov r13, 10

	mov rsi, number
	xor rax, rax

while:
	
	mov r8b, [rsi]
	cmp r8b, '$'
	je finish

	mul r13

	mov r8b, [rsi]
	sub r8b, '0'
	add rax, r8
	
	inc rsi
	jmp while	
	
		
finish:

	mov    rax, 60
   	mov    rdi, 0
   	syscall
