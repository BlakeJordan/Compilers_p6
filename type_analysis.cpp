#include "ast.hpp"
#include "symbol_table.hpp"
#include "types.hpp"

namespace lake {

void ProgramNode::typeAnalysis(TypeAnalysis * typing){
	myDeclList->typeAnalysis(typing);
	typing->nodeType(this, VarType::VOID());
}

void DeclListNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, VarType::VOID());
	for (auto decl : *myDecls){
		decl->typeAnalysis(typing);
		auto resType = typing->nodeType(decl);
		if (resType == nullptr){ throw InternalError(""); }
		if (resType->asError()){ 
			typing->nodeType(this, ErrorType::produce());
		}
	}
}

void IdNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, mySymbol->getType());
}

void DerefNode::typeAnalysis(TypeAnalysis * typing){
	myTgt->typeAnalysis(typing);
	const DataType * tgtType = typing->nodeType(myTgt);
	if (tgtType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}


	if (const VarType * asVar = tgtType->asVar()){
		const DataType * derefType = asVar->getDerefType();
		if (derefType == nullptr){
			typing->badDeref(getLine(), getCol());
			typing->nodeType(this, ErrorType::produce());
		} else {
			typing->nodeType(this, derefType);
		}
		return; 
	} else {
		//Attempt to deref a non-deref type
		typing->badDeref(getLine(), getCol());
		return; 
	}
}

void FormalDeclNode::typeAnalysis(TypeAnalysis * typing){
	//Declarations should be considered a base case for typeAnalysis
	typing->nodeType(this, myType->getDataType());
}

void VarDeclNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, myType->getDataType());
}

void VarDeclListNode::typeAnalysis(TypeAnalysis * typing){
	for (auto elt : *myDecls){
		elt->typeAnalysis(typing);
	}
	
	typing->nodeType(this, VarType::VOID());
}

void FormalsListNode::typeAnalysis(TypeAnalysis * typing){
	auto formalTypesList = new std::list<const DataType *>();

	for (auto elt : *myFormals){
		elt->typeAnalysis(typing);
		formalTypesList->push_back(typing->nodeType(elt));
	}
	typing->nodeType(this, new TupleType(formalTypesList));
}

void ExpListNode::typeAnalysis(TypeAnalysis * typing){
	auto childTypes = new std::list<const DataType *>();
	
	bool listErr = false;
	for (auto elt : *myExps){
		elt->typeAnalysis(typing);
		childTypes->push_back(typing->nodeType(elt));
	}
	typing->nodeType(this, new TupleType(childTypes));
}

void FnDeclNode::typeAnalysis(TypeAnalysis * typing){
	IdNode * idNode = getDeclaredID();
	if (idNode == NULL){ throw new InternalError("No id!"); }

	SemSymbol * sym = idNode->getSymbol();
	if (sym == NULL){ throw new InternalError("No symbol!"); }

	myFormals->typeAnalysis(typing);
	const TupleType * formalsType = 
		dynamic_cast<const TupleType *>(typing->nodeType(myFormals));


	FnType * myDataType = new FnType(formalsType, myRetAST->getDataType());
	typing->nodeType(this, myDataType);
	
	myBody->typeAnalysis(typing, myDataType);
}

void FnBodyNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myVarDecls->typeAnalysis(typing);
	myStmtList->typeAnalysis(typing, fn);
	typing->nodeType(this, VarType::VOID());
}

void StmtListNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	bool error = false;
	for (auto stmt : *myStmts){
		stmt->typeAnalysis(typing, fn);
		const DataType * stmtType = typing->nodeType(stmt);
		if (stmtType->asError()){
			error = true;
		}
	}

	if (error){
					typing->nodeType(this, ErrorType::produce());
	} else {
					typing->nodeType(this, VarType::VOID());
	}
}

static const DataType * typeAssignOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	//Errors are invalid, but don't cause re-reports
	if (type->asError()){ return nullptr; }

	//Valid types are returned
	if (type->asVar()){ return type; }

	//Invalid types are reported and skip operator check
	typing->badAssignOpd(opd->getLine(),opd->getCol());
	return nullptr;
}

void AssignNode::typeAnalysis(TypeAnalysis * typing){
	const DataType * tgtType = typeAssignOpd(typing, myTgt);
	const DataType * srcType = typeAssignOpd(typing, mySrc);

	if (!tgtType || !srcType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (tgtType == srcType){
		typing->nodeType(this, tgtType);
		return;
	}

	typing->badAssignOpr(getLine(), getCol());
	typing->nodeType(this, ErrorType::produce());
	return;
}

static void typeCallArgs(
	TypeAnalysis * typing, 
	const size_t callLine,
	const size_t callCol,
	const TupleType * formalsTypes,
	ExpListNode * actuals
){
	const TupleType * actualsTypes = 
		typing->nodeType(actuals)->asTuple();
	auto fList = formalsTypes->getElts();
	auto aList = actualsTypes->getElts();
	if (aList->size() != fList->size()){
		typing->badArgCount(callLine, callCol);
		return;
	} else {
		auto actualTypesItr = aList->begin();
		auto formalTypesItr = fList->begin();
		auto actualsItr = actuals->getExps()->begin();
		while(actualTypesItr != aList->end()){
			const DataType * actualType = *actualTypesItr;
			const DataType * formalType = *formalTypesItr;
			const ExpNode * actual = *actualsItr;
			actualTypesItr++;
			formalTypesItr++;
			actualsItr++;

			//Matching to error is ignored
			if (actualType->asError()){ continue; }
			if (formalType->asError()){ continue; }

			//Ok match
			if (formalType == actualType){ continue; }

			//Bad match
			typing->badArgMatch(actual->getLine(), actual->getCol());
		}
	}
	return;
}

void CallExpNode::typeAnalysis(TypeAnalysis * typing){
	myExpList->typeAnalysis(typing);

	SemSymbol * calleeSym = myId->getSymbol();
	const DataType * calleeType = calleeSym->getType();
	const FnType * fnType = calleeType->asFn();
	if (fnType == nullptr){
		typing->badCallee(myId->getLine(), myId->getCol());
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	typeCallArgs(
		typing,
		myId->getLine(),
		myId->getCol(),
		fnType->getFormalTypes(),
		myExpList
	);

	typing->nodeType(this, fnType->getReturnType());
	return;
}

void UnaryMinusNode::typeAnalysis(TypeAnalysis * typing){
	myExp->typeAnalysis(typing);
	const DataType * subType = typing->nodeType(myExp);

	//Propagate error, don't re-report
	if (subType->asError()){
		typing->nodeType(this, subType);
		return;
	}
	if (subType == VarType::produce(INT)){
		typing->nodeType(this, VarType::produce(INT));
	} else {
		typing->badMathOpd(getLine(), getCol());
		typing->nodeType(this, ErrorType::produce());
	}
}

void NotNode::typeAnalysis(TypeAnalysis * typing){
	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);
	if (childType == VarType::produce(BOOL)){
		typing->nodeType(this, childType);
	} else if (childType->asError() != nullptr){
		typing->nodeType(this, ErrorType::produce());
		return;
	} else {
		typing->badLogicOpd(myExp->getLine(), myExp->getCol());
		typing->nodeType(this, ErrorType::produce());
	}
}

static bool typeMathOpd(TypeAnalysis * typing, ExpNode * opd){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);
	if (type->isInt() || type->isPtr()){
		return true;
	}
	if (type->asError()){
		//Don't re-report an error, but don't check for
		// incompatibility
		return false;
	}

	typing->badMathOpd(opd->getLine(), opd->getCol());
	return false;
}


void BinaryExpNode::binaryMathTyping(
	TypeAnalysis * typing
){
	bool lhsValid = typeMathOpd(typing, myExp1);
	bool rhsValid = typeMathOpd(typing, myExp2);
	if (!lhsValid || !rhsValid){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	//Get the valid operand types, check operator
	const DataType * lhsType = typing->nodeType(myExp1);
	const DataType * rhsType = typing->nodeType(myExp2);

	if (lhsType->isInt() && rhsType->isInt()){
		typing->nodeType(this, VarType::produce(INT));
		return;
	}
	if (lhsType->isPtr() && rhsType->isInt()){
		typing->nodeType(this, lhsType);
		return;
	}
	if (lhsType->isInt() && rhsType->isPtr()){
		typing->nodeType(this, rhsType);
		return;
	}
	typing->badMathOpr(this->getLine(), this->getCol());
	typing->nodeType(this, ErrorType::produce());
	return;
}

static const DataType * typeLogicOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	//Return type if it's valid
	if (type->isBool()){ return type; }

	//Don't re-report an error, but return null to
	// indicate incompatibility
	if (type->asError()){ return nullptr; }

	//If type isn't an error, but is incompatible,
	// report and indicate incompatibility
	typing->badLogicOpd(opd->getLine(), opd->getCol());
	return NULL;
}

void BinaryExpNode::binaryLogicTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeLogicOpd(typing, myExp1);
	const DataType * rhsType = typeLogicOpd(typing, myExp2);
	if (!lhsType || !rhsType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	//Given valid operand types, check operator
	if (lhsType->isBool() && rhsType->isBool()){
		typing->nodeType(this, VarType::produce(BOOL));
		return;
	}

	//We never expect to get here, so we'll consider it
	// an error with the compiler itself
	throw new InternalError("Incomplete typing");
	typing->nodeType(this, ErrorType::produce());
	return;
}

void PlusNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void MinusNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void TimesNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void DivideNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void AndNode::typeAnalysis(TypeAnalysis * typing){
	binaryLogicTyping(typing);
}

void OrNode::typeAnalysis(TypeAnalysis * typing){
	binaryLogicTyping(typing);
}

static const DataType * typeEqOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	if (type->isInt()){ return type; }
	if (type->isPtr()){ return type; }
	if (type->isBool()){ return type; }

	//Errors are invalid, but don't cause re-reports
	if (type->asError()){ return nullptr; }

	typing->badEqOpd(opd->getLine(), opd->getCol());
	return nullptr;
}

void BinaryExpNode::binaryEqTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeEqOpd(typing, myExp1);
	const DataType * rhsType = typeEqOpd(typing, myExp2);

	if (!lhsType || !rhsType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (lhsType == rhsType){
		typing->nodeType(this, VarType::produce(BOOL));
		return;
	}
	if (lhsType->isInt() && rhsType->isPtr()){
		typing->nodeType(this, VarType::produce(BOOL));
		return;
	}
	if (lhsType->isPtr() && rhsType->isInt()){
		typing->nodeType(this, VarType::produce(BOOL));
		return;
	}

	typing->badEqOpr(getLine(), getCol());
	typing->nodeType(this, ErrorType::produce());
	return;
}

void EqualsNode::typeAnalysis(TypeAnalysis * typing){
	binaryEqTyping(typing);
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * typing){
	binaryEqTyping(typing);
}

static const DataType * typeRelOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	if (type->isInt()){ return type; }

	//Errors are invalid, but don't cause re-reports
	if (type->asError()){ return nullptr; }

	typing->badRelOpd(opd->getLine(),opd->getCol());
	typing->nodeType(opd, ErrorType::produce());
	return nullptr;
}

void BinaryExpNode::binaryRelTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeRelOpd(typing, myExp1);
	const DataType * rhsType = typeRelOpd(typing, myExp2);

	if (!lhsType || !rhsType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (lhsType->isInt() && rhsType->isInt()){
		typing->nodeType(this, VarType::produce(BOOL));
		return;
	}
	//There is no bad relational operator, so we never 
	// expect to get here
	return;
}

void LessNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void GreaterNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void LessEqNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void AssignStmtNode::typeAnalysis(
	TypeAnalysis * typing, FnType * fn
){
	myAssign->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myAssign);
	if (childType->asError()){
		typing->nodeType(this, ErrorType::produce());
	} else {
		typing->nodeType(this, VarType::VOID());
	}
}

static const DataType * typeUnaryMath(
	size_t line, size_t col,
	TypeAnalysis * typing, ExpNode * exp
){
	exp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(exp);

	//Propagate error but don't re-report
	if (childType->asError()){
		return ErrorType::produce();
	}

	//It's fine to do unary math on an int
	if (childType->isInt()){
		return childType;
	}

	//It's find to do unary math on any pointer
	if (childType->isPtr()){
		return childType;
	}

	//Any other unary math is an error
	typing->badMathOpr(line, col);
	return ErrorType::produce();
}

void PostIncStmtNode::typeAnalysis(
	TypeAnalysis * typing, FnType * fn
){
	typing->nodeType(this, typeUnaryMath(this->getLine(), 
		this->getCol(), typing, myExp));
}

void PostDecStmtNode::typeAnalysis(
	TypeAnalysis * typing, FnType * fn
){
	typing->nodeType(this, typeUnaryMath(this->getLine(), 
		this->getCol(), typing, myExp));
}

void ReadStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);
	const VarType * childAsVar = childType->asVar();

	if (childAsVar != nullptr){
		if (childAsVar->getDepth() > 0){
			typing->badReadPtr(getLine(),getCol());
			typing->nodeType(this, ErrorType::produce());
			return;
		}
	} else if (childType->asFn()){
		typing->readFn(getLine(),getCol());
		typing->nodeType(this, ErrorType::produce());
		return;
	}
	typing->nodeType(this, VarType::VOID());
}

void WriteStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);

	//Mark error, but don't re-report
	if (childType->asError()){
		typing->nodeType(this, childType);
		return;
	}

	//Check for invalid type
	if (childType == VarType::VOID()){
		typing->badWriteVoid(getLine(), getCol());
		typing->nodeType(this, ErrorType::produce());
		return;
	} else if (childType->asFn()){
		typing->writeFn(getLine(), getCol());
		typing->nodeType(this, ErrorType::produce());
		return;
	} else if (const VarType * asVar = childType->asVar()){
		if (asVar->getDepth() > 0){
			typing->writePtr(getLine(), getCol());
			typing->nodeType(this, ErrorType::produce());
			return;
		}
	}

	typing->nodeType(this, VarType::VOID());
}

void IfStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	//Start off the typing as void, but may update to error
	typing->nodeType(this, VarType::VOID());

	myExp->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myExp);
	if (condType->asError()){
		typing->nodeType(this, ErrorType::produce());
	} else if (condType != VarType::produce(BOOL)){
		typing->badIfCond(
			myExp->getLine(), 
			myExp->getCol());
		typing->nodeType(this, 
			ErrorType::produce());
	}

	myDecls->typeAnalysis(typing);
	myStmts->typeAnalysis(typing, fn);

}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myExp->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myExp);

	if (condType->asError()){
		typing->nodeType(this, ErrorType::produce());
	} else if (condType != VarType::produce(BOOL)){
		typing->badIfCond(myExp->getLine(), myExp->getCol());
	}
	myDeclsT->typeAnalysis(typing);
	myStmtsT->typeAnalysis(typing, fn);
	myDeclsF->typeAnalysis(typing);
	myStmtsF->typeAnalysis(typing, fn);
	
	typing->nodeType(this, VarType::produce(VOID));
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myExp->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myExp);

	if (condType->asError()){
		typing->nodeType(this, ErrorType::produce());
	} else if (condType != VarType::produce(BOOL)){
		typing->badWhileCond(myExp->getLine(), myExp->getCol());
	}

	myDecls->typeAnalysis(typing);
	myStmts->typeAnalysis(typing, fn);

	typing->nodeType(this, VarType::produce(VOID));
}

void CallStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	myCallExp->typeAnalysis(typing);
	typing->nodeType(this, VarType::VOID());
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * typing, FnType * fn){
	const FnType * fnType = fn;
	const DataType * fnRet = fnType->getReturnType();

	//Check: shouldn't return anything
	if (fnRet == VarType::VOID()){
		if (myExp != nullptr) {
			myExp->typeAnalysis(typing);
			typing->extraRetValue(
				myExp->getLine(), 
				myExp->getCol()); 
			typing->nodeType(this, ErrorType::produce());
		} else {
			typing->nodeType(this, VarType::VOID());
		}
		return;
	}

	//Check: returns nothing, but should
	if (myExp == nullptr){
			typing->badNoRet(getLine(), getCol());
			typing->nodeType(this, ErrorType::produce());
			return;
	}

	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);

	if (childType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (childType != fnRet){
		typing->badRetValue(myExp->getLine(), myExp->getCol());
		typing->nodeType(this, ErrorType::produce());
		return;
	}
	typing->nodeType(this, ErrorType::produce());
	return;
}

void StrLitNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, VarType::produce(BaseType::STR));
}

void TrueNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, VarType::produce(BaseType::BOOL));
}

void FalseNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, VarType::produce(BaseType::BOOL));
}

void IntLitNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, VarType::produce(BaseType::INT));
}

}
