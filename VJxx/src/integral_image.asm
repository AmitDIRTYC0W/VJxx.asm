global vjxx_integrate_image
global vjxx_sum_area

extern malloc
extern memset

section .text

vjxx_integrate_image:
	push	ebx
	push	esi
	push	edi
	
	; Extract parameters into registers.
        mov     edx, dword [esp + 20]		; edx <- src.width
	mov     eax, dword [esp + 24]		; eax <- src.height
        mov     edi, dword [esp + 16]		; edi <- address of dst
 
        ; UNSAFE BMP files might contain pictures, the sum of the pixels of which exceeds 32 bits.
 
 	; Set the width and height of the integral image (add 1 to both for the zero paddings).
        add	edx, 1				; edx <- original width + 1
        mov	dword [edi], edx		; width <- edx
        add	eax, 1				; eax <- original height + 1
        mov     dword [edi + 4], eax		; height <- eax
        
        ; Allocate values.
        shl	edx, 2				; edx <- width * sizeof(unsigned int)
        imul	eax, edx			; eax <- width * height * sizeof(unsigned int)
        push	eax
        call	malloc				; eax <- address of values
        mov	dword [edi + 8], eax
        ; UNSAFE malloc might fail.

        ; Create a zero-padding on the top row.
        mov	edx, dword [edi]		; edx <- width
        shl	edx, 2				; edx <- width * sizeof(unsigned int)
        push	edx				; width
        push	0				; the value zero
        push	eax				; dst.values
        call	memset
                
        ; Create a zero-padding on the left row.
        mov	ecx, dword [esp + 12]		; ecx <- width * height * sizeof(unsigned int)
        mov	edx, dword [edi]		; edx <- width
        mov	dword [esp], edx
        shl	edx, 2				; edx <- width * sizeof(unsigned int)
.left_zero_pad_head:
        sub	ecx, edx			; ecx <- ecx - width * sizeof(unsigned int)
        test	ecx, ecx
        jz	.left_zero_pad_exit

        mov	dword [eax + ecx], 0

        jmp	.left_zero_pad_head
.left_zero_pad_exit:
        
	; Integrate the values.
	xor	ebx, ebx			; ebx = y
	mov edx, 69 ;;;;;;;;;;;;;;;;
.y_loop_head:
	cmp	ebx, [esp + 40] ;;;;;;;;;;;;;;;;; src.height
	je	.y_loop_exit
	
	xor	ecx, ecx			; ecx = x
.x_loop_head:
	
	add ebx, 1 ;;;;;;;;;;;;;;;;;;;;
	add	ecx, 1
	
	mov	esi, ebx			; esi <- y
	imul	esi, [edi]			; esi <- width * y
	add	esi, ecx			; esi <- width * y + x
	mov	dword [eax + 4*esi], edx
	dec ebx ;;;;;;;;;;;;
	
	cmp	ecx, [esp + 36] ;;;;;;;;;;;;;;;;; [esp + 20] = src.width
	jne	.x_loop_head
	
	add	ebx, 1	
	jmp	.y_loop_head
.y_loop_exit:

        add	esp, 12
 
        ; Return.
        add	esp, 4
        pop	edi
        pop	esi
        pop	ebx
        ;int3        
        ret

vjxx_sum_area:
	; Extract parameters into registers.
        push    ebx
        push    edi
        push    esi
        mov     esi, dword [esp + 28]		; esi <- x0
        mov     ecx, dword [esp + 24]		; ecx <- address of img.values
        mov     ebx, dword [esp + 36]		; ebx <- x1
        mov     edx, dword [esp + 16]		; edx <- img.width
        mov     edi, dword [esp + 40]		; edi <- y1
        
        imul    edi, edx			; edi <- img.width * y1
        lea     eax, [edi + ebx]		; ebx <- bottom-right index
        mov     eax, dword [ecx + 4*eax]	; eax <- bottom-right value

        imul    edx, dword [esp + 32]		; edx <- img.width * y0
        add     ebx, edx			; ebx <- top-right index
        mov     ebx, dword [ecx + 4*ebx]	; ebx <- top-right value

        add     edi, esi			; edi <- bottom-left index
        add     ebx, dword [ecx + 4*edi]	; ebx <- top-right value + bottom-left value

        add     edx, esi			; edx <- top-left index 
        sub     eax, ebx			; eax <- bottom-right - (top-right + bottom-left)
        add     eax, dword [ecx + 4*edx]	; eax <- sum of the area
        
        ; Return.
        pop     esi
        pop     edi
        pop     ebx
        ret
