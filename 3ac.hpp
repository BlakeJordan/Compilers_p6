#ifndef LAKE_3AC_HPP
#define LAKE_3AC_HPP

#include "list"
#include "map"
#include "err.hpp"
#include "symbol_table.hpp"

namespace lake{

class Procedure;
class IRProgram;

class Label{
public:
	Label(std::string nameIn){
		this->name = nameIn;
	}
	std::string toString(){
		return "lbl_" + this->name;
	}
private:
	std::string name;
};

enum OpdType{
	STRING, NUMERIC
};

class Opd{
public:
	virtual std::string toString() = 0;
	virtual void genLoad(std::ostream& out, std::string dstReg="$t0") = 0;
	virtual void genStore(std::ostream& out, std::string srcReg="$t0") = 0;
	virtual OpdType getType() = 0;
};

class SymOpd : public Opd{
public:
	std::string toString() override{ 
		return mySym->getName();
	}
	const SemSymbol * getSym(){ return mySym; }
	virtual void genLoad(std::ostream& out, std::string loc) 
		override;
	virtual void genStore(std::ostream& out, std::string loc) 
		override;
	virtual void setMemoryLoc(std::string loc){
		myLoc = loc;
	}
	virtual std::string getMemoryLoc(){
		return myLoc;
	}
	virtual OpdType getType() override{
		//Normally we'd use the results of typechecking
		// here, but since variables are only ints and
		// bools (and we use a numeric type for both,
		// we just return numeric
		return NUMERIC;
	}
private:
	SymOpd(SemSymbol * sym) : mySym(sym) {} 
	SemSymbol * mySym;
	std::string myLoc;
	friend class Procedure;
	friend class IRProgram;
};

class LitOpd : public Opd{
public:
	LitOpd(std::string valIn) : val(valIn){ }
	std::string toString() override{
		return val;
	}
	virtual void genLoad(std::ostream& out, std::string loc) 
		override;
	virtual void genStore(std::ostream& out, std::string loc) 
		override;
	virtual OpdType getType() override{
		// Because string literals are represented using
		// AuxOpd, we know this literal is numeric
		return NUMERIC;
	}
private:
	std::string val;
};

class AuxOpd : public Opd{
public:
	AuxOpd(std::string nameIn, OpdType typeIn) 
	: name(nameIn), myType(typeIn) { }
	std::string toString() override{
		return name;
	}
	std::string getName(){
		return name;
	}
	virtual void genLoad(std::ostream& out, std::string loc)
		override;
	virtual void genStore(std::ostream& out, std::string loc) 
		override;
	virtual void setMemoryLoc(std::string loc){
		myLoc = loc;
	}
	virtual std::string getMemoryLoc(){
		return myLoc;
	}
	virtual OpdType getType() override{
		return myType;
	}
private:
	std::string name;
	std::string myLoc = "UNINIT";
	OpdType myType;
};

enum BinOp {
	ADD, SUB, DIV, MULT, OR, AND, EQ, NEQ, LT, GT, LTE, GTE
};
enum UnaryOp{
	NEG, NOT
};
enum Syscall {
	WRITE, READ, EXIT
};

class Quad{
public:
	Quad();
	void addLabel(Label * label);
	virtual std::string repr() = 0;
	std::string commentStr();
	virtual std::string toString(bool verbose=false);
	void setComment(std::string commentIn);
	virtual void codegenX64(std::ostream& out) = 0;
	void codegenLabels(std::ostream& out);
private:
	std::string myComment;
	std::list<Label *> labels;
};

class BinOpQuad : public Quad{
public:
	BinOpQuad(Opd * dstIn, BinOp opIn, Opd * src1In, Opd * src2In);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Opd * dst;
	BinOp op;
	Opd * src1;
	Opd * src2;
};

class UnaryOpQuad : public Quad {
public:
	UnaryOpQuad(Opd * dstIn, UnaryOp opIn, Opd * srcIn);
	std::string repr() override ;
	void codegenX64(std::ostream& out) override;
private:
	Opd * dst;
	UnaryOp op;
	Opd * src;
};

class AssignQuad : public Quad{
	
public:
	AssignQuad(Opd * dstIn, Opd * srcIn)
	: dst(dstIn), src(srcIn)
	{ }
	std::string repr() override;
	void codegenX64(std::ostream& out) override;

private:
	Opd * dst;
	Opd * src;
};

class LocQuad : public Quad {
public:
	LocQuad(Opd * srcIn, Opd * tgtIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Opd * src;
	Opd * tgt;
};

class JmpQuad : public Quad {
public:
	JmpQuad(Label * tgtIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Label * tgt;
};

class JmpIfQuad : public Quad {
public:
	JmpIfQuad(Opd * cndIn, bool invertIn, Label * tgtIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Opd * cnd;
	bool invert;
	Label * tgt;
};

class NopQuad : public Quad {
public:
	NopQuad();
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
};

class SyscallQuad : public Quad {
public:
	SyscallQuad(Syscall syscall, Opd * arg);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Opd * myArg;
	Syscall mySyscall;
};

class CallQuad : public Quad{
public:
	CallQuad(SemSymbol * calleeIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	SemSymbol * callee;
};

class EnterQuad : public Quad{
public:
	EnterQuad(Procedure * proc);
	virtual std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Procedure * myProc;
};

class LeaveQuad : public Quad{
public:
	LeaveQuad(Procedure * proc);
	virtual std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	Procedure * myProc;
};

class SetInQuad : public Quad{
public:
	SetInQuad(size_t indexIn, Opd * opdIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	size_t index;
	Opd * opd;
};

class GetInQuad : public Quad{
public:
	GetInQuad(size_t indexIn, Opd * opdIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	size_t index;
	Opd * opd;
};

class SetOutQuad : public Quad{
public:
	SetOutQuad(size_t indexIn, Opd * opdIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	size_t index;
	Opd * opd;
};

class GetOutQuad : public Quad{
public:
	GetOutQuad(size_t indexIn, Opd * opdIn);
	std::string repr() override;
	void codegenX64(std::ostream& out) override;
private:
	size_t index;
	Opd * opd;
};

class Procedure{
public:
	Procedure(IRProgram * prog, std::string name);
	void addQuad(Quad * quad);
	Quad * popQuad();
	IRProgram * getProg();
	lake::Label * makeLabel();

	void gatherLocal(SemSymbol * sym);
	void gatherFormal(SemSymbol * sym);
	SymOpd * getSymOpd(SemSymbol * sym);
	AuxOpd * makeTmp();

	std::string toString(bool verbose=false); 
	std::string getName();

	lake::Label * getLeaveLabel();

	void toX64(std::ostream& out);
	size_t numLocals() const;
	size_t numTemps() const;
private:
	void allocLocals();

	EnterQuad * enter;
	Quad * leave;
	Label * leaveLabel;

	IRProgram * myProg;
	std::map<SemSymbol *, SymOpd *> locals;
	std::list<AuxOpd *> temps; 
	std::list<SymOpd *> formals; 
	std::list<Quad *> bodyQuads;
	std::string myName;
	size_t maxTmp;
};

class IRProgram{
public:
	Procedure * makeProc(std::string name);
	Label * makeLabel();
	Opd * makeString(std::string val);
	void gatherGlobal(SemSymbol * sym);
	SymOpd * getGlobal(SemSymbol * sym);

	std::string toString(bool verbose=false);

	void toX64(std::ostream& out);
private:
	size_t max_label = 0;
	size_t str_idx = 0;
	std::list<Procedure *> procs; 
	HashMap<AuxOpd *, std::string> strings;
	std::map<SemSymbol *, SymOpd *> globals;

	void datagenX64(std::ostream& out);
	void allocGlobals();
};

}

#endif 
