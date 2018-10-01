;-----------------------------------------------------------------------------
;         		 This programm is emulating printf
;		returns 0 - equal
;		returns 1 - not equal
;------------------------------------------------------------------------------

section .text
	global _mystrcmp
_mystrcmp:

;-------------------------------------------------------------------
;		pushing arguments section

	nop
	nop
	nop
	nop
	
;	rdi, rsi

	xor rax, rax
	xor r8, r8
	xor r9, r9



while:

	xor rbx, rbx
	mov bl, byte [rdi]
	mov r8, rbx	

	xor rbx, rbx
	mov bl, byte [rsi]
	mov r9, rbx

	cmp r8, 0
	je zeroFound
	cmp r9, 0
	je zeroFound




	cmp r8, r9
	je notEqual

	mov rax, 1
	jmp endOfWord

notEqual:
		
	inc rdi
	inc rsi
	jmp while	

zeroFound:
	cmp r8, r9
	je endOfWord 

	mov rax, 1

endOfWord:		
	ret


; use lotsb

