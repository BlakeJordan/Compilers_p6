#include "3ac.hpp"
#include <stdio.h>

namespace lake{

Procedure::Procedure(IRProgram * prog, std::string name)
: myProg(prog), myName(name){
	maxTmp = 0;
	enter = new EnterQuad(this);
	if (myName.compare("main") == 0){
		leave = new SyscallQuad(EXIT, nullptr);
	} else {
		leave = new LeaveQuad(this);
	}
	leaveLabel = myProg->makeLabel();
	leave->addLabel(leaveLabel);
}

std::string Procedure::getName(){
	return myName;
}

Label * Procedure::getLeaveLabel(){
	return leaveLabel;
}

IRProgram * Procedure::getProg(){ return myProg; }

std::string Procedure::toString(bool verbose){
	std::string res = "";

	res += "[BEGIN " + this->getName() + " LOCALS]\n";
	for (const auto formal : this->formals){
		res += formal->toString() + " (formal)\n";
	}

	for (auto local : this->locals){
		res += local.second->toString() + " (local)\n";
	}

	for (auto tmp : temps){
		res += tmp->toString() + " (tmp)\n";
	}
	res += "[END " + this->getName() + " LOCALS]\n";

	res += enter->toString(verbose) + "\n";
	for (auto quad : bodyQuads){
		res += quad->toString(verbose) + "\n";
	}
	res += leave->toString(verbose) + "\n";
	return res;
}

Label * Procedure::makeLabel(){
	return myProg->makeLabel();
}

void Procedure::addQuad(Quad * quad){
	bodyQuads.push_back(quad);
}

Quad * Procedure::popQuad(){
	Quad * last = bodyQuads.back();
	bodyQuads.pop_back();
	return last;
}

void Procedure::gatherLocal(SemSymbol * sym){
	locals[sym] = new SymOpd(sym);
}

void Procedure::gatherFormal(SemSymbol * sym){
	formals.push_back(new SymOpd(sym));
}

SymOpd * Procedure::getSymOpd(SemSymbol * sym){
	for(auto formalSeek : formals){
		if (formalSeek->getSym() == sym){
			return formalSeek;
		}
	}

	auto localFound = locals.find(sym);
	if (localFound != locals.end()){
		return localFound->second;
	}
	
	return this->getProg()->getGlobal(sym);
}

AuxOpd * Procedure::makeTmp(){
	std::string name = "tmp";
	name += std::to_string(maxTmp++);
	AuxOpd * res = new AuxOpd(name, NUMERIC);
	temps.push_back(res);

	return res;
}

size_t Procedure::numTemps() const{
	return this->temps.size();
}

size_t Procedure::numLocals() const{
	return this->locals.size();
}

}
