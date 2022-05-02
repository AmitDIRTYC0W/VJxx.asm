global main

section .data
invalid_usage_msg:	db	"ERROR: invalid usage", 0xa
invalid_usage_msg_len:	equ	$ - invalid_usage_msg

section .text

main:
	push	ebp
	mov	ebp, esp
	
	; Check the validity of the command line arguments.
	cmp	dword [ebp + 8], 2 		; If argc equals 2,
	je	invalid_usage_exit		; continue.
	
	mov	eax, 4				; write syscall
	mov	ebx, 2				; fd <- stderr
	mov	ecx, invalid_usage_msg		; buf
	mov	edx, invalid_usage_msg_len	; count
	int	0x80

invalid_usage_exit:
	;int3
	
	leave
	ret