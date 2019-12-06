#include "ast.hpp"

namespace lake {

ASTNode::ASTNode(size_t lineIn, size_t colIn){
	this->line = lineIn;
	this->col = colIn;
}
void ASTNode::doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << " "; }
}
size_t ASTNode::getLine()const { return line; }
size_t ASTNode::getCol() const { return col; }
std::string ASTNode::getPosition(){
	std::string res = "";
	res += std::to_string(getLine());
	res += ":";
	res += std::to_string(getCol());
	return res;
}

IdNode::IdNode(IDToken * token)
: ExpNode(token->_line, token->_column), 
  myStrVal(token->value()),
  mySymbol(NULL){ }

std::string IdNode::getString(){ return myStrVal; }

DeclNode::DeclNode(size_t lIn, size_t cIn, IdNode * idIn)
: ASTNode(lIn, cIn), myID(idIn){ }

std::string DeclNode::getDeclaredName(){
	return myID->getString();
}

IdNode * DeclNode::getDeclaredID(){
	return myID;
}

ProgramNode::ProgramNode(DeclListNode * declListIn)
: ASTNode(0,0), myDeclList(declListIn){ }

TypeNode::TypeNode(size_t lnIn, size_t colIn)
: ASTNode(lnIn, colIn), myPtrDepth(0){}

void TypeNode::setPtrDepth(size_t depth){
	myPtrDepth = depth;
}

DerefNode::DerefNode(size_t lnIn, size_t colIn, ExpNode * tgt)
: ExpNode(lnIn, colIn), myTgt(tgt){ }

} //End namespace lake
