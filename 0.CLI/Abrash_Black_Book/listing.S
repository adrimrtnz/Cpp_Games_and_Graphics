	.file	"L1-5.c"
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "Usage: checksum filename\0"
.LC1:
	.ascii "Cant't open file %s\12\0"
.LC2:
	.ascii "Can't get enough memory\0"
.LC3:
	.ascii "Error reading file %s\12\0"
.LC4:
	.ascii "The checksum is: %u\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	__main
	cmpl	$2, 16(%rbp)
	je	.L2
	leaq	.LC0(%rip), %rcx
	call	puts
	movl	$1, %eax
	jmp	.L3
.L2:
	movq	24(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$32768, %edx
	movq	%rax, %rcx
	call	open
	movl	%eax, -24(%rbp)
	cmpl	$-1, -24(%rbp)
	jne	.L4
	movq	24(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rcx
	call	printf
	movl	$1, %eax
	jmp	.L3
.L4:
	movl	$32768, %ecx
	call	malloc
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L5
	leaq	.LC2(%rip), %rcx
	call	puts
	movl	$1, %eax
	jmp	.L3
.L5:
	movl	$0, -4(%rbp)
.L9:
	movq	-32(%rbp), %rdx
	movl	-24(%rbp), %eax
	movl	$32768, %r8d
	movl	%eax, %ecx
	call	read
	movl	%eax, -36(%rbp)
	cmpl	$-1, -36(%rbp)
	jne	.L6
	movq	24(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	leaq	.LC3(%rip), %rcx
	call	printf
	movl	$1, %eax
	jmp	.L3
.L6:
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L7
.L8:
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	addl	%eax, -4(%rbp)
.L7:
	movl	-20(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -20(%rbp)
	testl	%eax, %eax
	jne	.L8
	cmpl	$0, -36(%rbp)
	jne	.L9
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC4(%rip), %rcx
	call	printf
	movl	$0, %eax
.L3:
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 4.9.2"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	open;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	read;	.scl	2;	.type	32;	.endef
