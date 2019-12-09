#include "3ac.hpp"
#include "vector"

namespace lake {

Procedure * IRProgram::makeProc(std::string name){
	Procedure * proc = new Procedure(this, name);
	procs.push_back(proc);
	return proc;
}

Label * IRProgram::makeLabel(){
	Label * label = new Label(std::to_string(max_label++));
	return label;
}

SymOpd * IRProgram::getGlobal(SemSymbol * sym){
	if (globals.find(sym) != globals.end()){
		return globals[sym];
	} 
	return nullptr;
}

void IRProgram::gatherGlobal(SemSymbol * sym){
	SymOpd * res = new SymOpd(sym);
	globals[sym] = res;
}

Opd * IRProgram::makeString(std::string val){
	std::string name = "str_" + std::to_string(str_idx++);
	AuxOpd * opd = new AuxOpd(name, STRING);
	strings[opd] = val;
	return opd;
}

std::string IRProgram::toString(bool verbose){
	std::string res = "";
	res += "[BEGIN GLOBALS]\n";
	for (auto entry : globals){
		res += entry.second->toString() + "\n"; 
	}
	for (auto entry : strings){
		res += entry.first->toString(); 
		res += " " + entry.second; 
		res += "\n";
	}

	res += "[END GLOBALS]\n";
	
	for (Procedure * proc : procs){
		res += proc->toString(verbose);
	}
	return res;
}

}
