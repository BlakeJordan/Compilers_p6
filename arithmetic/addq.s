.text
.globl _start
_start:
	movq $2, %r12
	movq $4, %r13
	addq %r12, %r13
	addq %r13, %r13
	
	movq %r13, %rdi
	movq $60, %rax	
	syscall
