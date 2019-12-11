.data
globl_d: .quad 0
globl_z: .quad 0
.align 8

.text
lbl_f:
	subq $8, %rsp
	movq %rbp, (%rsp)
	movq %rsp, %rbp
	addq $16, %rbp
	subq $8, %rsp
	movq 0(%rbp), %rdi
	jmp lbl_0
lbl_0: 
	addq $16, $rsp
	movq (%rsp), %rbp
	addq $8, %rsp
lbl_main:
	subq $8, %rsp
	movq %rbp, (%rsp)
	movq %rsp, %rbp
	addq $16, %rbp
	subq $16, %rsp
	movq $0, %rax
	movq %rax, 8(%rbp)
	movq $6, %rax
	movq %rax, (gbl_z)
	movq $1, %rax
	movq %rax, (gbl_d)
	movq $4, %rax
	movq %rax, 0(%rbp)
	movq $2, %rax
	movq $3, %rbx
	imulq %rbx
	movq (%rbx), %rax
	movq (%rbx), %rax
	movq %rax, 0(%rbp)
	movq 0(%rbp), %rax
	movq (gbl_z), %rbx
	cmpq %rbx, %rax
	setl %al
	movq (%rbx), %rax
	movq (%rbx), %rax
	jne lbl_2
	movq $5, %rax
	movq $4, %rbx
	subq %rbx, %rax
	movq (%rbx), %rax
	movq (%rbx), %rax
	movq %rax, 0(%rbp)
lbl_2: 
	nop
	movq $0, %rdx
	movq $2, %rax
	movq $3, %rbx
	idivq %rbx
	movq (%rbx), %rax
	movq (%rbx), %rax
	movq %rax, 0(%rbp)
	movq 0(%rbp), %rax
	movq $1, %rbx
	addq %rbx, %rax
	movq %rax, 0(%rbp)
	movq 0(%rbp), %rax
	movq $1, %rbx
	subq %rbx, %rax
	movq %rax, 0(%rbp)
	movq 0(%rbp), %rdi
	callq printInt
	movq 8(%rbp), %rax
	movq %rsp, -8(%rsp)
	movq %rax, 0(%rsp)
	jmp lbl_f
	movq $0, %rdi
	jmp lbl_1
lbl_1: 
	movq $60, %rax
	movq $0, rdi
	syscall
