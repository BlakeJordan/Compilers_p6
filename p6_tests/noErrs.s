.data
func_f:
EnterQuad_codeGen (implement)
SetOutQuad_codeGen (implement)
jmp lbl_0
lbl_0: LeaveQuad_codeGen (implement)
func_main:
EnterQuad_codeGen (implement)
movq $8%rax
SymOpd_genStore (implement)
movq $8%rax
SymOpd_genStore (implement)
SyscallQuad_codeGen (implement)
je lbl_2
SyscallQuad_codeGen (implement)
lbl_2: nop
SetInQuad_codeGen (implement)
CallQuad_codeGen (implement)
lbl_1: SyscallQuad_codeGen (implement)
