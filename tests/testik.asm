section .text


	global _myStrcmp
_myStrcmp:


	nop
        nop
        nop

        xor rax, rax

while:

	cmp byte [rsi] , 0
        je zeroFound

        cmpsb
        je notEqual

        mov rax, 1
        jmp endOfWord

notEqual:

        jmp while

zeroFound:
        cmp byte [rdi], 0
        je endOfWord
        mov rax, 1
	
        endOfWord:

	
ret
