;-----------------------------------------------------------------------------
;         		 This programm is emulating printf
;------------------------------------------------------------------------------

section.data

	first$problem 	db "expected $ in the beginnig"
	char$problem1 	db "expected $ in the beginning of char argument"
	char$problem2 	db "expected $ in the end of char argument"
	string$problem1 db "expected $ in the beginning of string argument"
	string$problem2 db "expected $ in the end of char argument"
	numScaleProblem	db "Scale wasn`t pointed or it is wrong"

	argument1 db "LOVE$"
	argument2 db "Iamarg2$"
	
	charAscii	db "0"


	message db "He %b %%%oworld!! And %c %s %h %d %%",0

section.text 
	global _start
_start:

;-------------------------------------------------------------------
;		pushing arguments section

	push 100
	push 3802
	push argument1
	push 'I'
	push 15566
	push 15566

	
;-------------------------------------------------------------------

	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, message			
   	mov     rdx, 1

	

while:					; while, that runs through all letters 
					; and searches '%'
	mov r8b, [rsi]

	cmp r8b, '%'			; found an argument
	je argumentFound	

	cmp r8b, 0
	je finish

	syscall
	inc rsi
	jne while	


	


	


	




	
;--------finish-------------------------------------------

finish:
   	mov    rax, 60
   	mov    rdi, 0
   	syscall


;===============================================================================

;----------------------------------------------------------
;		this function finds first argument
;		  and puts its ',' pointer in r8
;	destruct:	
;----------------------------------------------------------

argumentFound: 	
	
	inc rsi
	mov r8b, [rsi]
	
	cmp r8b, 'c'
	je printChar

	cmp r8b, 's'	
	je printString

	cmp r8b, 'd'	
	mov r12, 10
	je printNum10

	cmp r8b, 'b'
	je printNum2

	cmp r8b, 'o'
	je printNum8
	
	cmp r8b, 'h'
	je printNum16

	cmp r8b, '%'
	je printPercent

endOfSwitch:


	jmp while

;------------------------------------------------------------------------

printPercent:

	syscall
	
	inc rsi
	jmp endOfSwitch
	

;------------------------------------------------------------------------
printChar:
	
	push rsi

	mov rsi, rsp
	add rsi, 8

	syscall
	pop rsi			; print char

	pop r8
	xor r8, r8

	inc rsi

	jmp endOfSwitch

;----------------------------------------------------------
printString:

	push rsi

	mov rsi, [rsp + 8 ]
		

	
stringWhile:
	
	mov r8b, [rsi]
	cmp r8b, '$'
	je  stringContinue
	
	syscall
	inc rsi
	jne stringWhile

stringContinue:
	
	pop rsi

	pop r8
	xor r8, r8
	
	inc rsi

	jmp endOfSwitch



;=============================================================
;			printNum
;	This function is printing a number in scale you want
;	
;	Entry:	r12 - scale
;
;	Exit:	
;
;	Destr:
;		
;=============================================================

printNum10:

	mov r15, rsi
 	

	mov rbp, rsp
	mov eax, dword [rbp]
	mov edx, dword [rbp + 4]

	xor r14, r14
	
	
diversity:

	nop

	div r12w
	cmp edx, 10
	jl less10
	cmp edx, 9
	jg more9		;choosing where to jump
	

less10:		
	add edx, '0'    		; ASCII-code from 0 to 9
	jmp anyway

more9:
	add edx, ('A' - 10) 	; ASCII-code from A to F
	jmp anyway


anyway:
		; remembering
	

	push rdx
	xor rdx, rdx

	inc r14

	cmp rax, 0
	jne diversity

	mov rax, 1
	mov rdi, 1
	mov rdx, 1

printingNum:
	mov rsi, rsp
	syscall

	pop r8
	xor r8, r8

	sub r14, 1
		
	cmp r14, 0
	jne printingNum
	
	pop r8
	xor r8, r8	
	
	mov rsi, r15
	
	inc rsi

	jmp endOfSwitch

;--------------------------------------------------------------------------------
;================================================================================
;		This function is printing in scale 2
;
;	Entry:	TopStack - argument
;
;	Destr:	 r8, r15, r14, rax, rdx,
;
;================================================================================




printNum2

	mov r15, rsi

	pop rax

binaryDiv:
	
	mov rdx, rax
	and rdx, 1
	
	add rdx, '0'
	push rdx
	inc r14

	shr rax, 1
	cmp rax, 0
	jne binaryDiv

	call PrintingNum

	mov rsi, r15
	
	inc rsi

	jmp endOfSwitch

;--------------------------------------------------------------------------------
;================================================================================
;		This function is printing in scale 8
;
;	Entry:	TopStack - argument
;
;	Destr:	 r8, r15, r14, rax, rdx,
;
;================================================================================




printNum8

	mov r15, rsi

	pop rax

octDiv:
	
	mov rdx, rax
	and rdx, 7
	
	add rdx, '0'
	push rdx
	inc r14

	shr rax, 3
	cmp rax, 0
	jne octDiv

	call PrintingNum

	mov rsi, r15
	
	inc rsi

	jmp endOfSwitch

	

;--------------------------------------------------------------------------------
;================================================================================
;		This function is printing in scale 16
;
;	Entry:	TopStack - argument
;
;	Destr:	 r8, r15, r14, rax, rdx,
;
;================================================================================




printNum16

	mov r15, rsi

	pop rax

hexDiv:
	
	mov rdx, rax
	and rdx, 15
	
	cmp rdx, 10
	jl AsciiNum
	cmp rdx, 9
	jg AsciiLet		;choosing where to jump
	

AsciiNum:		
	add edx, '0'    		; ASCII-code from 0 to 9
	jmp bothWays

AsciiLet:
	add edx, ('A' - 10) 	; ASCII-code from A to F
	jmp bothWays


bothWays:


	push rdx
	inc r14

	shr rax, 4
	cmp rax, 0
	jne hexDiv

	call PrintingNum	

	mov rsi, r15
	
	inc rsi

	jmp endOfSwitch

;-----------------------------------------------------------------------------
;===========================================================================
;		Printing a number in Stack
;
;	Entry:	Stack with ASCII-codes of numbers
;		r14 - number of numbers
;
;	Destr: r8, r14, rax, rdi, rdx
;
;============================================================================



PrintingNum:

	pop rbp

cycleFor:
	mov rax, 1
	mov rdi, 1
	mov rdx, 1

	mov rsi, rsp
	syscall

	pop r8
	xor r8, r8

	sub r14, 1
		
	cmp r14, 0
	jne cycleFor

	push rbp
	ret












;----------------------------------------------------------
problem1:
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, first$problem			
   	mov     rdx, 26
	syscall

	jmp finish
;----------------------------------------
problem2:
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, char$problem1			
   	mov     rdx, 44
	syscall

	jmp finish
;----------------------------------------
problem3:
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, char$problem2			
   	mov     rdx, 38
	syscall

	jmp finish
;----------------------------------------
problem4:
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, string$problem1			
   	mov     rdx, 46
	syscall

	jmp finish
;----------------------------------------
problem5:
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, string$problem2			
   	mov     rdx, 40
	syscall

	jmp finish
;----------------------------------------
problem6:	
	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, numScaleProblem			
   	mov     rdx, 40
	syscall

	jmp finish


