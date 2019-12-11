.data
gbl_d:
.quad 0
gbl_z:
.quad 0
.align 8

.text
.globl _start
.globl main
_start:

fun_main:
	subq $8, %rsp
	movq %rbp, (%rsp)
	movq %rsp, %rbp
	addq $16, %rbp
	subq $32, %rsp
	movq $0, %rax
	movq %rax, -32(%rbp)
	movq $6, %rax
	movq %rax, (gbl_z)
	movq $1, %rax
	movq %rax, (gbl_d)
	movq $4, %rax
	movq %rax, -24(%rbp)
	movq $2, %rax
	movq $3, %rbx
	imulq %rbx
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	movq %rax, -24(%rbp)
	movq $0, %rdx
	movq $2, %rax
	movq $3, %rbx
	idivq %rbx
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq $1, %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq $1, %rbx
	subq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rdi
	callq printInt
	movq $0, %rdi
	jmp lbl_0
lbl_0: 
	movq $60, %rax
	syscall
