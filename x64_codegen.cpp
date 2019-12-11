#include <ostream>
#include "3ac.hpp"
#include "err.hpp"
#include "stdlake.c"

size_t formals_size = 0;
size_t locals_size = 0;
namespace lake{

void IRProgram::allocGlobals(){
	for (auto global : globals) {
		SymOpd * globalOpd = global.second;
		std::string memLoc = "gbl_";
		const SemSymbol * sym = globalOpd->getSym();
		memLoc += sym->getName();
		globalOpd->setMemoryLoc("(" + memLoc + ")");
	}
	for (auto string : strings) {
		AuxOpd * strHandle = string.first;
		std::string memLoc = "str_" + strHandle->getName();
		strHandle->setMemoryLoc(memLoc);
	}
	// TODO(Implement me)
}

void IRProgram::datagenX64(std::ostream& out){
	out << ".data\n";
	allocGlobals();
	for(auto global : globals) {
		Opd * globalOpd = global.second;
		out << "gbl_" 
			<< globalOpd->toString()
			<< ":\n" 
			<< ".quad"
			<< " 0"
			<< "\n";
	}

	for(auto string : strings) {
		std::string strData = string.second;
		AuxOpd * strHandle = string.first;
		out << strHandle->getMemoryLoc()
			<< ":\n"
			<< ".asciz"
			<< strData
			<< "\n";
			// finish this
	}
	out << ".align 8\n\n";
	out << ".text\n";
	out << ".globl _start\n";
	for(auto procedure : procs) {
		out << ".globl " << procedure->getName() << "\n";
	}
	out << "_start:\n\n";
	// TODO(Implement me)
}

void IRProgram::toX64(std::ostream& out){
	datagenX64(out);
	for(auto procedure : procs) {
		procedure->makeLabel();
		procedure->toX64(out);
	}
	// TODO(Implement me)
}

void Procedure::allocLocals(){
	formals_size = formals.size();
	locals_size = locals.size();
	int offset = 24;
	int localPos = 0;
	for(auto local : locals) {
		SymOpd * localOpd = local.second;
		//int localOffset = localOffset - localPos * 8;
		std::string memLoc = "-" + std::to_string(offset);
		memLoc += "(%rbp)";
		localOpd->setMemoryLoc(memLoc);
		offset = offset + 8;
	}
	for(auto temp : temps) {
		//int tempOffset = -24 - tempPos * 8;
		std::string memLoc = "-" + std::to_string(offset);
		memLoc += "(%rbp)";
		temp->setMemoryLoc(memLoc);
		offset = offset + 8;
	}
	int formalPos = 0;
	for(auto formalOpd : formals) {
		// double check
		int formalOffset = formalPos * 8;
		std::string memLoc = std::to_string(formalOffset);
		memLoc += "(%rbp)";
		formalOpd->setMemoryLoc(memLoc);
		formalPos++;
	}
	int tempPos = 0;

}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	out << "fun_" << myName << ":" << "\n";

	enter->codegenX64(out);
	for (auto quad : bodyQuads){
		quad->codegenLabels(out);
		quad->codegenX64(out);
	}
	leave->codegenLabels(out);
	leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream& out){
	if (labels.empty()){ return; }

	size_t numLabels = labels.size();
	size_t labelIdx = 0;
	for (Label * label : labels){
		out << label->toString() << ": ";
		if (labelIdx != numLabels - 1){ out << "\n"; }
		labelIdx++;
		out << "\n";
	}
}

// https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
// https://piazza.com/class_profile/get_resource/j7ly9riuca97on/ja86xbbpp0b73b
void BinOpQuad::codegenX64(std::ostream& out){
	// out << "\n\n#Start BinOp\n";
	if(op == DIV) {
		out << "\tmovq $0, %rdx\n";
		src1->genLoad(out, "%rax");
		src2->genLoad(out, "%rbx");
		out << "\tidivq %rbx\n";
		dst->genStore(out, "%rax");
		return;
	} else if (op == MULT) {
		src1->genLoad(out, "%rax");
		src2->genLoad(out, "%rbx");
		out << "\timulq %rbx\n";
		dst->genStore(out, "%rax");
		return;
	}
	src1->genLoad(out, "%rax");
	src2->genLoad(out, "%rbx");
	switch(op) {
		case DIV: break;
		case MULT: break;
		case ADD: out << "\taddq %rbx, %rax\n"; break;
		case SUB: out << "\tsubq %rbx, %rax\n"; break;
		case OR: out  << "\torq $1, %rbx\n"; out << "cmpq $1, %rax\n"; break;
		case AND: out << "\tandq $1, %rbx\n"; out << "cmpq $1, %rax\n"; break;
		case EQ: out  << "\tcmpq %rbx, %rax\n"
					  << "\tsete %al\n"; break;
		case NEQ: out << "\tcmpq %rbx, %rax\n"
					  << "\tsetne %al\n"; break;
		case LT: out  << "\tcmpq %rbx, %rax\n"
					  << "\tsetl %al\n"; break;
		case GT: out  << "\tcmpq %rbx, %rax\n"
						// double check
					  << "\tsetg %al\n"; break;
		case LTE: out << "\tcmpq %rbx, %rax\n"
					  << "\tsetle %al\n"; break;
		case GTE: out << "\tcmpq %rbx, %rax\n"
						// double check
					  << "\tsetge %al\n"; break;
		default: break;
	}
	dst->genStore(out, "%rax");
	// out << "\n#End BinOp\n\n";
	return;
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	src->genLoad(out, "%rax");
	if(op == NEG)
	{
		out << "\tneg %rax";
	}
	else if(op == NOT)
	{
		out << "\tnot %rax";
	} 
	// TODO(Implement me)
}

void AssignQuad::codegenX64(std::ostream& out){
	// out << "\n\n#START AssignQuad_codeGen\n";
	src->genLoad(out, "%rax");
	dst->genStore(out, "%rax");
	// out << "#END AssignQuad_codeGen\n\n";

}

void LocQuad::codegenX64(std::ostream& out){
	// out << "#LocQuad_codeGen\n";
}

void JmpQuad::codegenX64(std::ostream& out){
	out << "\tjmp " << tgt->toString() << "\n";
}

void JmpIfQuad::codegenX64(std::ostream& out){
	cnd->genLoad(out, "%rax");
	if(invert)
	{
		out << "\tje " << tgt->toString() << "\n";
	}
	else
	{
		out << "\tjne " << tgt->toString() << "\n";
	}
	
	//TODO(Implement me)
}

void NopQuad::codegenX64(std::ostream& out){
	out << "\tnop" << "\n";
}

void SyscallQuad::codegenX64(std::ostream& out){
	if(mySyscall == WRITE)
	{
		if(myArg->getType() == 1)
		{
			myArg->genLoad(out, "%rdi");
			out << "\tcallq printInt\n";
		}
		else if(myArg->getType() == 0)
		{
			myArg->genLoad(out, "%rdi");
			out << "\tcallq printString\n";
		}
	}
	else if(mySyscall == READ)
	{
		myArg->genLoad(out, "%rdi");
		out << "\tcallq getInt\n";
	}
	else if(mySyscall == EXIT)
	{
		out << "\tmovq $60, %rax\n";
		//out << "\tmovq $0, %rdi\n";
		out << "\tsyscall\n";
	}
}

void CallQuad::codegenX64(std::ostream& out){
	out << "\tcallq fun_" << callee->getName() << "\n";
	out << "\taddq $" << 8*callee->getType()->asFn()->getFormalTypes()->getElts()->size() << ", %rsp\n";
}

void EnterQuad::codegenX64(std::ostream& out){
	out << "\tsubq $8, %rsp\n";
	out << "\tmovq %rbp, (%rsp)\n";
	out << "\tmovq %rsp, %rbp\n";
	out << "\taddq $16, %rbp\n";
	out << "\tsubq $" << std::to_string(8*(myProc->numLocals() + myProc->numTemps())) << ", %rsp\n";
}

void LeaveQuad::codegenX64(std::ostream& out){
	out << "\taddq $" << std::to_string(8*(myProc->numLocals() + myProc->numTemps())) << ", %rsp\n";
	out << "\tmovq (%rsp), %rbp\n";
	out << "\taddq $8, %rsp\n";
	out << "\tret\n";
}

void SetInQuad::codegenX64(std::ostream& out){
	opd->genLoad(out, "%rax");
	out << "\tsubq $8, %rsp\n";
	out << "\tmovq %rax, 0(%rsp)\n";
}

void GetInQuad::codegenX64(std::ostream& out){
	//We don't actually need to do anything here
}

void SetOutQuad::codegenX64(std::ostream& out){
	opd->genLoad(out, "%rdi");
}

void GetOutQuad::codegenX64(std::ostream& out){
	opd->genStore(out, "%rdi");
}

void SymOpd::genLoad(std::ostream & out, std::string regStr){
	// out << "#SymOpd_genLoad\n";
	out << "\tmovq " << myLoc << ", " << regStr << "\n";
}

void SymOpd::genStore(std::ostream& out, std::string regStr){
	// out << "#SymOpd_genStore\n";
	out << "\tmovq " << regStr << ", " << myLoc << "\n"; 
}

void AuxOpd::genLoad(std::ostream& out, std::string regStr){
	// out << "#AuxOpd_genLoad\n";
	if(myLoc == "UNINIT")
	{
		setMemoryLoc("%rbx");
	}
	out << "\tmovq " << myLoc << ", " << regStr <<"\n"; 
}

void AuxOpd::genStore(std::ostream& out, std::string regStr){
	// out << "#AuxOpd_genStore\n";
	if(myLoc == "UNINIT")
	{
		setMemoryLoc("%rbx");
	}
	out << "\tmovq " << regStr << ", " << myLoc << "\n";
}

void LitOpd::genLoad(std::ostream& out, std::string regStr){
	// out << "#litOpd_genLoad\n";
	out << "\tmovq $" << val << ", " << regStr << "\n"; 
}

void LitOpd::genStore(std::ostream& out, std::string regStr){
	throw new InternalError("Cannot use literal as l-val");
}

}
