.text
.globl _start
_start:
	movq $2, %rax
	imulq $4, %rax
	movq %rax, %r12
	
	movq $60, %rax	
	movq %r12, %rdi
	syscall
