.text
.globl _start
_start:
	movq $0, %rdx    #upper 64 bits of divisor
	movq $6, %rax   #lower 64 bits of divisor
	
	movq $2, %r8    # The denominator
	idivq %r8	# Do the deed
	movq %rax, %r12	# move the quotient into r12
	movq %rdx, %r13 # move the remainder into r13
	
	movq $60, %rax	
	movq %r13, %rdi
	syscall
