.text
.globl _start
_start:
	movq $2, %r12
	movq $4, %r13
	subq %r12, %r13
	
	movq %r13, %rdi
	movq $60, %rax	
	syscall
