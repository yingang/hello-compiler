	.data
int_format:
	.string "%d\n"
trues:
	.string "true\n"
falses:
	.string "false\n"
a:
	.int 0
b:
	.int 0


	.text
	.globl main
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$88

	pushl	$1

	leave
	ret
	.globl printi
printi:
	push	%ebp
	movl	%esp, %ebp
	pushl	8(%ebp)
	pushl	$int_format
	call	printf
	leave
	ret
	.globl printb
printb:
	push	%ebp
	movl	%esp, %ebp
	xorl	%eax, %eax
	cmpl	8(%ebp), %eax
	je	.L_f
	pushl	$trues
	jmp	.L_e
.L_f:
	pushl	$falses
.L_e:
	call	puts
	leave
	ret
