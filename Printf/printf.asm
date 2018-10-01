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

	message db "$He%clo wor%sd!!$, $l$, $lalalala$"

section.text 
	global _start
_start:

	mov     rax, 1
   	mov     rdi, 1
   	mov     rsi, message			
   	mov     rdx, 1

	
	mov	r8b, [rsi]
	cmp	r8b, '$'
	jne	problem1

	call findFirstArg

while:					; while, that runs through all letters 
					; and searches '%'
	inc rsi
	mov r8b, [rsi]

	cmp r8b, '%'			; found an argument
	je argumentFound	

	cmp r8b, '$'
	je finish

	syscall
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

findFirstArg:	
	mov rbx, message

repeat:
	inc rbx
	mov r8b, [rbx]

	cmp r8b, '$'
	jne repeat

	inc rbx
	
	xor r8b, r8b
	ret
	endp


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
	je printNum

	cmp r8b, 'b'	
	mov r12, 2
	je printNum

	cmp r8b, 'o'	
	mov r12, 8
	je printNum

	cmp r8b, 'р'
	mov r12, 16
	je printNum

endOfSwitch:

	jmp while

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

printNum:

	inc rbx			; miss comma

	inc rbx			; miss probel
	push rsi		; save rsi ( position ) 
	mov rsi, rbx
	mov r8b, [rsi]
	
	cmp r8b, 'b'		; choosing 
	je scaleB
	cmp r8b, 'o'
	je scaleO
	cmp r8b, 'd'
	je scaleD
	cmp r8b, 'h'
	je scaleH
	jmp problem6

scaleB:	mov r13, 2
	jmp choosingArgScaleFin

scaleO:	mov r13, 8
	jmp choosingArgScaleFin

scaleD:	mov r13, 10
	jmp choosingArgScaleFin

scaleH:	mov r13, 16
	jmp choosingArgScaleFin

choosingArgScaleFin:


	xor rax, rax
	inc rsi
	
scanningNum:
	
	mov r8b, [rsi]
	cmp r8b, ','
	je stopScanning
	cmp r8b, '$'
	je stopScanning
	cmp r8b, ' '
	je stopScanning

	mul r13

	mov r8b, [rsi]
	cmp r8b, '9'
	jae scannedNumber

	cmp r8b, '9'
	jg scannedLetter

scannedNumber:

	sub r8b, '0'
	jmp scannedLorN
	
scannedLetter:
	
	sub r8b, 'a'
	add r8b, 10
	jmp scannedLorN

scannedLorN:

	
	add rax, r8

	inc rsi
	jmp scanningNum

stopScanning:

	

;-------------------------------------------------------------
printChar:
	
	inc rbx			; miss probel

	inc rbx
	mov r8b, [rbx]
	cmp r8b, '$'
	jne problem2		; check beginning '$'

	inc rbx
	push rsi
	mov rsi, rbx
	syscall
	pop rsi			; print char

	inc rbx	
	mov r8b, [rbx]
	cmp r8b, '$'
	jne problem3		; check ending '$'

	inc rbx			; put pointer on ','

	jmp endOfSwitch

;----------------------------------------------------------
printString:

	inc rbx			; miss probel

	inc rbx
	mov r8b, [rbx]
	cmp r8b, '$'
	jne problem4		; check beginning '$'

	push rsi
	mov rsi, rbx
	
stringWhile:
	inc rsi
	mov r8b, [rsi]
	cmp r8b, '$'
	je  stringContinue
	
	syscall
	jne stringWhile

stringContinue:
	
	mov rbx, rsi
	pop rsi

	inc rbx			; put pointer on ','

	jmp endOfSwitch

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


