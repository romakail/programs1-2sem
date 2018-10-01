;-----------------------------------------------------------------------------
;          Press a button and I will write its ascii code in
;		 binar, octal and hexademical system.
;-----------------------------------------------------------------------------
.model tiny


;---------------------------------------------------------------------
;	DATA:

	Color		=	04eh		;

	LeftUp 		=	0c9h		;
	HorLine		=	0cdh		;
	RightUp 	=	0bbh		;
	VerLine 	=	0bah		;
	RightDown	=	0bch		;
	LeftDown	=	0c8h		;
	Probel		=	020h		;
	
	Lenght          =	20		;
	Height		=	6		;
;---------------------------------------------------------------------




.code
org 100h

start:          mov bx, 0b800h
                mov es, bx
                
                std             
		
		call DrawFrame
               
		mov ah, 00h
		int 16h
		xor ah, ah	; scancod disappearence
		mov bl, al
		
		mov di, 1680
		mov es: [di], bl	
		inc di
		mov es: [di], Color

		mov di, 1840
                mov dx, 2d      ; preparing printing in binary number

		call PrintNumber ; printing  /2

		mov al, bl
		xor ah, ah
		mov di, 2000
		mov dx, 8d	; preparing printing in octal number
		
		call PrintNumber ; printing  /8
				
		mov al, bl
		xor ah, ah
		mov di, 2160
		mov dx, 16d	; preparing printing in octal number
		
		call PrintNumber ; printing  /16

		mov al, bl
		xor ah, ah
		mov di, 2320
		mov dx, 10d	; preparing printing in octal number
		
		call PrintNumber ; printing /10
		
                mov ax, 4c00h   ; exit
                int 21h

;======================================================================================
;		this function is printing a number in notation scale you want
;		
;		Entry:	AX - Number
;			DI - position offset from 0b800h
;			DX - Notation scale
;			ES - 0b800h
;			
;		Exit:	nothing interesting
;
;		Destr:	AX DX
;======================================================================================




;----------------------------------------------------------------------------
PrintNumber	proc

divercity:      div dl          
		cmp ah, 10
		jl less10
		cmp ah, 9
		jg more9	; choosing where to jump



less10:		add ah, '0'     ; ASCII-code from 0 to 9
		jmp anyway

more9:		add ah, ('A' - 10) ; ASCII-code from A to F
		jmp anyway

anyway:
                mov dh, al      ; remembering result of diversion
                xchg ah, al     ; changing result and fission
                mov ah, 4eh     ; adding colour

               	stosw
                mov al, dh      ; returning result
                mov ah, 0       ; zeroing out the fission
                cmp al, 0       ; do not repeat if the result is 0
                jne divercity
		
		ret
		endp
;============================================================================
;	this function is drawing a frame in the centre
;	
;	Entry:	ES - 08b00h
;
;	Exit:	--
;
;	Destr:	BX AX SI
;==============================================================================

DrawFrame	proc

	mov ax, 0b800h
	mov es, ax
	
	mov bx, ( 80 * ( 23 - Height ) + ( 80 - Lenght ) + 80)

;--------------------------------------LeftUp---------------------------------

	mov es: [bx], leftup
	inc bx
	mov es: [bx], 4eh
	
	mov ax, 0 

;----------------------------------HorizontalLine-----------------------------

firstLine:
	inc bx
	mov es: [bx], HorLine
	inc bx
	mov es: [bx], Color
	
	inc ax
	
	cmp ax, Lenght
	jne firstLine

;----------------------------------RightUp-----------------------------------

	inc bx
	mov es: [bx], RightUp
	inc bx
	mov es: [bx], Color

	xor si, si
iLine:	
	add bx, ( 80 - Lenght - 2 ) * 2

;----------------------------------VerticalLine--------------------------------

	inc bx
	mov es: [bx], VerLine
	inc bx
	mov es: [bx], Color

;---------------------------------HorizontalSpacec-----------------------------

	xor ax,ax

probLine:
	inc bx
	mov es: [bx], probel
	inc bx
	mov es: [bx], Color
	
	inc ax
	
	cmp ax, Lenght
	jne probLine

;---------------------------------VerticalLine---------------------------------
	inc bx
	mov es: [bx], VerLine
	inc bx
	mov es: [bx], Color
	
	inc si	
	cmp si, Height
	jb iLine	
	
	
	add bx, ( 80 - Lenght - 2 ) * 2

;---------------------------------LeftDown-------------------------------------

	inc bx
	mov es: [bx], LeftDown
	inc bx
	mov es: [bx], Color

;---------------------------------HorizontalLine--------------------------------

	xor ax, ax
LastLine:
	inc bx
	mov es: [bx], HorLine
	inc bx
	mov es: [bx], Color
	
	inc ax
	
	cmp ax, Lenght
	jne LastLine

;----------------------------------RightDown----------------------------------

	inc bx
	mov es: [bx], RightDown
	inc bx
	mov es: [bx], Color
	
	ret
	endp
;------------------------------------------------------------------------------------

		
end start
;----------------------------------------------------------------------------
;                     		The End
;----------------------------------------------------------------------------