#include "ast.hpp"

namespace lake{

IRProgram * ProgramNode::to3AC(){
	IRProgram * prog = new IRProgram();
	myDeclList->to3AC(prog);
	return prog;
}

void VarDeclListNode::to3AC(Procedure * proc){
	for (auto decl : *myDecls){
		decl->to3AC(proc);
	}
}

void DeclListNode::to3AC(IRProgram * prog){
	for (auto decl : *myDecls){
		decl->to3AC(prog);
	}
}

void FnDeclNode::to3AC(IRProgram * prog){
	SemSymbol * mySym = getDeclaredID()->getSymbol();
	Procedure * proc = prog->makeProc(mySym->getName());

	

	//Generate the getin quads
	myFormals->to3AC(proc);

	myBody->to3AC(proc);
}

void FnDeclNode::to3AC(Procedure * proc){
	throw new InternalError("FnDecl at a local scope");
}

Opd * DerefNode::flatten(Procedure * proc){
	throw new InternalError("Deref nodes have been dropped from P6");
}

//We only get to this node if we are in a stmt
// context (DeclNodes protect descent) 
Opd * IdNode::flatten(Procedure * proc){
	SemSymbol * sym = this->getSymbol();
	Opd * res = proc->getSymOpd(sym);
	if (!res){
		throw new InternalError("null id sym");;
	}
	return res;
}

void FormalDeclNode::to3AC(IRProgram * prog){
	throw new InternalError("Formal at a global level");
}

void FormalDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = getDeclaredID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	proc->gatherFormal(sym);
}

void FormalsListNode::to3AC(Procedure * proc){
	for (auto formal : *myFormals){
		formal->to3AC(proc);
	}
	unsigned int argIdx = 1;
	for (auto formal : *myFormals){
		SemSymbol * sym = formal->getDeclaredID()->getSymbol();
		SymOpd * opd = proc->getSymOpd(sym);
		
		Quad * inQuad = new GetInQuad(argIdx, opd);
		proc->addQuad(inQuad);
		argIdx += 1;
	}
}

void ExpListNode::to3AC(Procedure * proc){
	size_t argIdx = 1;
	for (auto elt : *myExps){
		Opd * arg = elt->flatten(proc);
		Quad * argQuad = new SetInQuad(argIdx, arg);
		proc->addQuad(argQuad);
		argIdx++;
	}
}

void StmtListNode::to3AC(Procedure * proc){
	for (auto stmt : *myStmts){
		stmt->to3AC(proc);
	}
}

void FnBodyNode::to3AC(Procedure * proc){
	myVarDecls->to3AC(proc);
	myStmtList->to3AC(proc);
}

Opd * IntLitNode::flatten(Procedure * proc){
	return new LitOpd(std::to_string(myInt));
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myString);
	return res;
}

Opd * TrueNode::flatten(Procedure * prog){
	Opd * res = new LitOpd("1");
	return res;
}

Opd * FalseNode::flatten(Procedure * prog){
	Opd * res = new LitOpd("0");
	return res;
}

Opd * AssignNode::flatten(Procedure * proc){
	Opd * rhs = mySrc->flatten(proc);
	Opd * lhs = myTgt->flatten(proc);
	if (!lhs){
		throw InternalError("null tgt");
	}
	
	AssignQuad * quad = new AssignQuad(lhs, rhs);
	quad->setComment("Assign");
	proc->addQuad(quad);
	return lhs;
}

Opd * CallExpNode::flatten(Procedure * proc){
	myExpList->to3AC(proc);
	Quad * callQuad = new CallQuad(myId->getSymbol());
	proc->addQuad(callQuad);

	SemSymbol * idSym = myId->getSymbol();
	const FnType * calleeType = idSym->getType()->asFn();
	if (calleeType->getReturnType()->isVoid()){
		return nullptr;
	} else {
		Opd * retVal = proc->makeTmp();
		Quad * getRet = new GetOutQuad(1, retVal);
		proc->addQuad(getRet);
		return retVal;
	}
}

Opd * UnaryMinusNode::flatten(Procedure * proc){
	Opd * child = myExp->flatten(proc);
	Opd * dst = proc->makeTmp();
	Quad * quad = new UnaryOpQuad(dst, NEG, child);
	proc->addQuad(quad);
	return dst;
}

Opd * NotNode::flatten(Procedure * proc){
	Opd * child = myExp->flatten(proc);
	Opd * dst = proc->makeTmp();
	Quad * quad = new UnaryOpQuad(dst, NOT, child);
	proc->addQuad(quad);
	return dst;
}

Opd * PlusNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	Opd * dst = proc->makeTmp();
	Quad * quad = new BinOpQuad(dst, ADD, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * MinusNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	Opd * dst = proc->makeTmp();
	Quad * quad = new BinOpQuad(dst, SUB, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * TimesNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	Opd * dst = proc->makeTmp();
	Quad * quad = new BinOpQuad(dst, MULT, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * DivideNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, DIV, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * AndNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, AND, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * OrNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, OR, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * EqualsNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, EQ, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, NEQ, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * LessNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, LT, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * GreaterNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, GT, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * LessEqNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, LTE, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	Opd * opRes = proc->makeTmp();
	BinOpQuad * quad = new BinOpQuad(opRes, GTE, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

void AssignStmtNode::to3AC(Procedure * proc){
	Opd * res = myAssign->flatten(proc);
	// Since we're at the stmt level, we know
	// this opd isn't going to be used. We 
	// could delete it
}

void PostIncStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myExp->flatten(proc);
	LitOpd * litOpd = new LitOpd("1");
	BinOpQuad * quad = new BinOpQuad(child, ADD, child, litOpd);
	proc->addQuad(quad);
}

void PostDecStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myExp->flatten(proc);
	LitOpd * litOpd = new LitOpd("1");
	BinOpQuad * quad = new BinOpQuad(child, SUB, child, litOpd);
	proc->addQuad(quad);
}

void ReadStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myExp->flatten(proc);
	SyscallQuad * quad = new SyscallQuad(READ, child);
	proc->addQuad(quad);
}

void WriteStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myExp->flatten(proc);
	SyscallQuad * quad = new SyscallQuad(WRITE, child);
	proc->addQuad(quad);
}

void IfStmtNode::to3AC(Procedure * proc){
	Opd * cond = myExp->flatten(proc);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);

	proc->addQuad(new JmpIfQuad(cond, false, afterLabel));
	myDecls->to3AC(proc);
	myStmts->to3AC(proc);
	proc->addQuad(afterNop);
}

void IfElseStmtNode::to3AC(Procedure * proc){
	Label * elseLabel = proc->makeLabel();
	Quad * elseNop = new NopQuad();
	elseNop->addLabel(elseLabel);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);

	Opd * cond = myExp->flatten(proc);

	Quad * jmpFalse = new JmpIfQuad(cond, false, elseLabel);
	proc->addQuad(jmpFalse);
	myDeclsT->to3AC(proc);
	myStmtsT->to3AC(proc);
	
	Quad * skipFall = new JmpQuad(afterLabel);
	proc->addQuad(skipFall);

	proc->addQuad(elseNop);
	
	myDeclsF->to3AC(proc);
	myStmtsF->to3AC(proc);

	proc->addQuad(afterNop);
}

void WhileStmtNode::to3AC(Procedure * proc){
	Quad * headNop = new NopQuad();
	Label * headLabel = proc->makeLabel();
	headNop->addLabel(headLabel);

	Label * afterLabel = proc->makeLabel();
	Quad * afterQuad = new NopQuad();
	afterQuad->addLabel(afterLabel);

	proc->addQuad(headNop);
	Opd * cond = myExp->flatten(proc);
	Quad * jmpFalse = new JmpIfQuad(cond, false, afterLabel);
	proc->addQuad(jmpFalse);

	myDecls->to3AC(proc);
	myStmts->to3AC(proc);

	Quad * loopBack = new JmpQuad(headLabel);
	proc->addQuad(loopBack);
	proc->addQuad(afterQuad);
}

void CallStmtNode::to3AC(Procedure * proc){
	Opd * res = myCallExp->flatten(proc);
	//Since we're in a callStmt, the GetOut quad
	// generated as the last action of the subtree
	// was unnecessary. Remove it from the procedure.
	if (res != nullptr){
		//A void call will not generate a getout
		Quad * last = proc->popQuad();
	}
	//Should probably delete the last quad, but
	// we've leaked so much memory why start worrying now?
}

void ReturnStmtNode::to3AC(Procedure * proc){
	if (myExp != nullptr){
		Opd * res = myExp->flatten(proc);
		Quad * setOut = new SetOutQuad(1, res);
		proc->addQuad(setOut);
	}
	
	Label * leaveLbl = proc->getLeaveLabel();
	Quad * jmpLeave = new JmpQuad(leaveLbl);
	proc->addQuad(jmpLeave);
}

void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = getDeclaredID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	proc->gatherLocal(sym);
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = getDeclaredID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	
	prog->gatherGlobal(sym);
}

}
