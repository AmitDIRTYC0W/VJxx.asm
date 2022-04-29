global vjxx_haar_x2
global vjxx_haar_y2
global vjxx_haar_x3
global vjxx_haar_y3
global vjxx_haar_x2y2

extern vjxx_sum_area

section .text

; int vjxx_haar_x2(
;	struct vjxx_integral_image img,
;	unsigned int x0,
;	unsigned int y0,
;	unsigned int width,
;	unsigned int height
; )
vjxx_haar_x2:
	; Preserve registers.
	push	ebp
	mov	ebp, esp
	push	ebx
	push	esi
	
	; Calculate the sum of the left area.
	mov	eax, dword [ebp + 24]		; eax <- y0
	mov	edx, dword [ebp + 32]		; edx <- height
	add	edx, eax			; edx <- y0 + height
	push	edx				; y1	

	mov     ebx, dword [ebp + 28]		; ebx <- width
	shr	ebx, 1				; ebx <- width / 2
	mov	esi, dword [ebp + 20]		; esi <- x0
	add	ebx, esi			; ebx <- x0 + width / 2
	push	ebx				; x1

	push	eax				; y0
	push	esi				; x0

	push	dword [esp + 40]		; img.values
	push	dword [esp + 40]		; img.height
	push	dword [esp + 40]		; img.width

	call	vjxx_sum_area
	
	; Calculate the sum of the right area.
	mov	[esp + 12], ebx			; x0
	add	esi, dword [ebp + 28]		; esi <- x0 + width
	mov	[esp + 20], esi			; x1
	
	mov	ebx, eax			; Preserve the left sum.
	
	call	vjxx_sum_area
	
	; Subtract the right sum from the left sum.
	sub	eax, ebx
	neg	eax

	pop	esi
	pop	ebx
	leave
	ret

vjxx_haar_y2:
	ret

vjxx_haar_x3:
	ret

vjxx_haar_y3:
	ret

vjxx_haar_x2y2:
	ret