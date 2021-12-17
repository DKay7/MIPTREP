	.file	"task8.cpp"
	.text
	.globl	_Z3leni
	.type	_Z3leni, @function
_Z3leni:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$1, -4(%rbp)
	movl	$1, -8(%rbp)
.L3:
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	.L2
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
	jmp	.L3
.L2:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	_Z3leni, .-_Z3leni
	.globl	_Z3recii
	.type	_Z3recii, @function
_Z3recii:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	cmpl	$1, -24(%rbp)
	jne	.L6
	movl	$1, %eax
	jmp	.L7
.L6:
	cmpl	$1, -20(%rbp)
	jne	.L8
	movl	-24(%rbp), %eax
	jmp	.L7
.L8:
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	_Z3leni
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	addl	$1, %eax
	cmpl	%eax, -20(%rbp)
	setg	%al
	testb	%al, %al
	je	.L9
	movl	-24(%rbp), %eax
	leal	-1(%rax), %ebx
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	_Z3leni
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	movl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%ebx, %esi
	movl	%eax, %edi
	call	_Z3recii
	jmp	.L7
.L9:
	movl	-24(%rbp), %eax
	leal	-1(%rax), %edx
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z3recii
	nop
.L7:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	_Z3recii, .-_Z3recii
	.section	.rodata
.LC0:
	.string	"%d %d"
.LC1:
	.string	"%c\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB17:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-16(%rbp), %rdx
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z3recii
	addl	$96, %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
