#include "ast.hpp"
#include "symbol_table.hpp"
#include "errName.hpp"
#include "types.hpp"

namespace lake{

const DataType * IntNode::getDataType(){
	return VarType::produce(BaseType::INT, getPtrDepth());
}

const DataType * VoidNode::getDataType(){
	if (getPtrDepth() != 0){
		throw new InternalError("non-zero void depth!");
	}
	return VarType::produce(BaseType::VOID, getPtrDepth());
}

const DataType * BoolNode::getDataType(){
	return VarType::produce(BaseType::BOOL, getPtrDepth());
}

std::string TypeNode::getTypeString(){
	return this->getDataType()->getString();
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	//Enter the global scope
	symTab->enterScope();
	bool res = this->myDeclList->nameAnalysis(symTab);
	//Leave the global scope
	symTab->leaveScope();
	return res;
}

bool VarDeclListNode::nameAnalysis(SymbolTable * symTab){
	bool res = true;
	for (auto elt : *myDecls){
		res = elt->nameAnalysis(symTab) && res;
	}
	return res;
}

bool TypeNode::nameAnalysis(SymbolTable * symTab){
	throw new InternalError("Name analysis should"
		" never reach type nodes");
}

bool AssignStmtNode::nameAnalysis(SymbolTable * symTab){
	return myAssign->nameAnalysis(symTab);
}

bool PostIncStmtNode::nameAnalysis(SymbolTable * symTab){
	return myExp->nameAnalysis(symTab);
}

bool PostDecStmtNode::nameAnalysis(SymbolTable * symTab){
	return myExp->nameAnalysis(symTab);
}

bool ReadStmtNode::nameAnalysis(SymbolTable * symTab){
	return myExp->nameAnalysis(symTab);
}

bool WriteStmtNode::nameAnalysis(SymbolTable * symTab){
	return myExp->nameAnalysis(symTab);
}

bool IfStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myExp->nameAnalysis(symTab) && result;
	symTab->enterScope();
	result = myDecls->nameAnalysis(symTab) && result;
	result = myStmts->nameAnalysis(symTab) && result;
	symTab->leaveScope();
	return result;
}

bool IfElseStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myExp->nameAnalysis(symTab) && result;
	symTab->enterScope();
	result = myDeclsT->nameAnalysis(symTab) && result;
	result = myStmtsT->nameAnalysis(symTab) && result;
	symTab->leaveScope();
	symTab->enterScope();
	result = myDeclsF->nameAnalysis(symTab) && result;
	result = myStmtsF->nameAnalysis(symTab) && result;
	symTab->leaveScope();
	return result;
}

bool WhileStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	symTab->enterScope();
	result = myExp->nameAnalysis(symTab) && result;
	result = myDecls->nameAnalysis(symTab) && result;
	result = myStmts->nameAnalysis(symTab) && result;
	symTab->leaveScope();
	return result;
	
}

bool DeclListNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	for (auto decl : *myDecls){
		result = decl->nameAnalysis(symTab) && result;
	}
	return result;
}

bool StmtListNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	for (auto elt : *myStmts){
		result = elt->nameAnalysis(symTab) && result;
	}
	return result;
}

static bool dataDecl(SymbolTable * symTab, DeclNode * decl, TypeNode * typeNode){
	const DataType * dataType = typeNode->getDataType();
	bool validType = true;

	const VarType * varObj = dataType->asVar();
	if (!varObj){
		throw InternalError("Variable without variable type");
	}

	if (varObj->getBaseType() == BaseType::VOID){
		if (varObj->getDepth() > 0){
			NameErr::badPointer(decl->getLine(), decl->getCol()); 
		} else {
			NameErr::badVoid(decl->getLine(), decl->getCol()); 
		}
		validType = false;
	}

	std::string varName = decl->getDeclaredName();
	bool validName = !symTab->clash(varName);
	if (!validName){ 
		NameErr::multiDecl(decl->getLine(), decl->getCol()); 
	}

	if (!validType || !validName){ return false; }

	SemSymbol * sym = new SemSymbol(VAR, dataType, varName);
	decl->getDeclaredID()->attachSymbol(sym);
	symTab->insert(sym);
	return true;
}

bool VarDeclNode::nameAnalysis(SymbolTable * symTab){
	return dataDecl(symTab, this, this->getTypeNode());
}

bool FormalDeclNode::nameAnalysis(SymbolTable * symTab){
	return dataDecl(symTab, this, this->getTypeNode());
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	std::string fnName = this->getDeclaredName();
	const DataType * retType = myType->getReturnType();
	const VarType * retVarType = retType->asVar();
	if (retVarType->getBaseType() == BaseType::VOID){
		if (retVarType->getDepth() > 0){
			NameErr::badPointer(
				myRetAST->getLine(),
				myRetAST->getCol());
		}
		//It's ok for a function to have a void return type
	}

	// hold onto the scope where the function itself is
	ScopeTable * atFnScope = symTab->getCurrentScope();
	//Enter a new scope for this function.
	ScopeTable * inFnScope = symTab->enterScope();

	bool validFormals = myFormals->nameAnalysis(symTab);
	const TupleType * formalsType = myType->getFormalTypes();

	//Note that we check for a clash of the function name in
	// the scope at which it exists (i.e. the function scope)
	bool validName = !atFnScope->clash(fnName);
	if (validName == false){
		NameErr::multiDecl(
			getDeclaredID()->getLine(), 
			getDeclaredID()->getCol()); 
	}

	//Make sure the fnSymbol is in the symbol table before 
	// analyzing the body, to allow for recursive calls
	if (validName && validFormals){
		FnType * fnType = new FnType(formalsType, retType);
		SemSymbol * fnSym = new SemSymbol(FN, fnType, fnName);
		atFnScope->insert(fnSym);
		getDeclaredID()->attachSymbol(fnSym);
	}

	bool validBody = myBody->nameAnalysis(symTab);

	symTab->leaveScope();
	return (validName && validFormals && validBody);
}

bool FormalsListNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	for (auto elt : *myFormals){
		result = elt->nameAnalysis(symTab) && result;
	}
	return result;
}

bool FnBodyNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myVarDecls->nameAnalysis(symTab) && result;
	result = myStmtList->nameAnalysis(symTab) && result;
	return result;
}

bool BinaryExpNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myExp1->nameAnalysis(symTab) && result;
	result = myExp2->nameAnalysis(symTab) && result;
	return result;
}

bool ExpListNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	for (auto elt : *myExps){
		result = elt->nameAnalysis(symTab) && result;
	}
	return result;
}

bool CallExpNode::nameAnalysis(SymbolTable* symTab){
	bool result = true;
	result = myId->nameAnalysis(symTab) && result;
	result = myExpList->nameAnalysis(symTab) && result;
	return result;
}

bool UnaryMinusNode::nameAnalysis(SymbolTable* symTab){
	return myExp->nameAnalysis(symTab);
}

bool NotNode::nameAnalysis(SymbolTable* symTab){
	return myExp->nameAnalysis(symTab);
}

bool AssignNode::nameAnalysis(SymbolTable* symTab){
	bool result = true;
	result = myTgt->nameAnalysis(symTab) && result;
	result = mySrc->nameAnalysis(symTab) && result;
	return result;
}

bool ReturnStmtNode::nameAnalysis(SymbolTable * symTab){
	if (myExp == nullptr){
		return true;
	}
	return myExp->nameAnalysis(symTab);
}

bool CallStmtNode::nameAnalysis(SymbolTable* symTab){
	return myCallExp->nameAnalysis(symTab);
}

bool DerefNode::nameAnalysis(SymbolTable * symTab){
	return myTgt->nameAnalysis(symTab);
}

bool IdNode::nameAnalysis(SymbolTable* symTab){
	std::string myName = this->getString();
	SemSymbol * sym = symTab->find(myName);
	if (sym == nullptr){
		return NameErr::undecl(this->getLine(), getCol());
	}
	this->attachSymbol(sym);
	return true;
}

void IdNode::attachSymbol(SemSymbol * symbolIn){
	this->mySymbol = symbolIn;
}

SemSymbol * IdNode::getSymbol(){
	return this->mySymbol;
}

}
