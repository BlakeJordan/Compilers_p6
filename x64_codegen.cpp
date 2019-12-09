#include <ostream>
#include "3ac.hpp"
#include "err.hpp"

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
	for(auto string : strings) {
		std::string strData = string.second;
		AuxOpd * strHandle = string.first;
		out << strHandle->getMemoryLoc()
			<< ":"
			<< " .asciz"
			<< strData
			<< "\n";
			// finish this
	}
	// TODO(Implement me)
}

void IRProgram::toX64(std::ostream& out){
	datagenX64(out);
	allocGlobals();
	for(auto procedure : procs) {
		procedure->toX64(out);
	}
	// TODO(Implement me)
}

// https://docs.google.com/document/d/1zefHUZg7h-lhQKEZnv2E10ndsyZkR3yMobn7W668tiE/edit?usp=sharing
void Procedure::allocLocals(){
	size_t localPos = 0;
	// int numLocal= locals.size;
	for(auto local : locals) {
		SymOpd * localOpd = local.second;
		size_t localOffset = localPos * 8;
		std::string memLoc = std::to_string(localOffset);
		memLoc += "(%rbp)";
		localOpd->setMemoryLoc(memLoc);
		localPos++;
	}

	size_t formalPos = 0;
	// int numFormals = formals.size;
	for(auto formalOpd : formals) {
		// double check
		size_t formalOffset = formalPos * 8;
		std::string memLoc = std::to_string(formalOffset);
		memLoc += "(%rbp)";
		formalOpd->setMemoryLoc(memLoc);
		formalPos++;
	}
	// TODO(Implement me)
}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	out << "func_" << myName << ":" << "\n";

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
	}
}

// https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
void BinOpQuad::codegenX64(std::ostream& out){
	out << "#BinOp\n";
	if(op == DIV) {
		out << "movq $0, %rdx\n";
		src1->genLoad(out, "%rax");
		src2->genLoad(out, "%rbx");
		out << "idivq %rbx\n";
		dst->genStore(out, "%rax");
		return;
	} else if (op == MULT) {
		src1->genLoad(out, "%rax");
		src2->genLoad(out, "%rbx");
		out << "imulq %rbx\n";
		return;
	}
	src1->genLoad(out, "%rax");
	src2->genLoad(out, "%rbx");
	switch(op) {
		case DIV: break;
		case MULT: break;
		case ADD: out << "addq %rax, %rbx\n"; break;
		case SUB: out << "subq %rax, %rbx\n"; break;
		case OR: out  << "orq $1, %rax\n"; out << "cmpq $1, %rbx\n"; break;
		case AND: out << "andq $1, %rax\n"; out << "cmpq $1, %rbx\n"; break;
		case EQ: out  << "cmpq %rax, %rbx\n"
					  << "sete %al\n"; break;
		case NEQ: out << "cmpq %rax, %rbx\n"
					  << "setne %al\n"; break;
		case LT: out  << "cmpq %rax, %rbx\n"
					  << "setl %al\n"; break;
		case GT: out  << "cmpq %rax, %rbx\n"
						// double check
					  << "setg %al\n"; break;
		case LTE: out << "cmpq %rax, %rbx\n"
					  << "setle %al\n"; break;
		case GTE: out << "cmpq %rax, %rbx\n"
						// double check
					  << "setge %al\n"; break;
	}
	// TODO(Implement me)
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void AssignQuad::codegenX64(std::ostream& out){
	src->genLoad(out, "%rax");
	dst->genStore(out, "%rax");
}

void LocQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void JmpQuad::codegenX64(std::ostream& out){
	out << "jmp " << tgt->toString() << "\n";
}

void JmpIfQuad::codegenX64(std::ostream& out){
	out << "je " << tgt->toString() << "\n";
	//TODO(Implement me)
}

void NopQuad::codegenX64(std::ostream& out){
	out << "nop" << "\n";
}

void SyscallQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void CallQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void EnterQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void LeaveQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void SetInQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void GetInQuad::codegenX64(std::ostream& out){
	//We don't actually need to do anything here
}

void SetOutQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void GetOutQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void SymOpd::genLoad(std::ostream & out, std::string regStr){
	out << "movq " << myLoc << regStr << "\n"; 
	// TODO(Implement me)
}

void SymOpd::genStore(std::ostream& out, std::string regStr){
	TODO(Implement me)
}

void AuxOpd::genLoad(std::ostream & out, std::string regStr){
	TODO(Implement me)
}

void AuxOpd::genStore(std::ostream& out, std::string regStr){
	TODO(Implement me)
}

void LitOpd::genLoad(std::ostream & out, std::string regStr){
	TODO(Implement me)
}

void LitOpd::genStore(std::ostream& out, std::string regStr){
	throw new InternalError("Cannot use literal as l-val");
}

}
