#include "types.hpp"
#include <list>
#include <sstream>

namespace lake{

std::string VarType::getString() const{
	std::string res = "";
	switch(myBaseType){
	case INT:
		res += "int";
		break;
	case BOOL:
		res += "bool";
		break;
	case BaseType::VOID:
		res += "void";
		break;
	case STR:
		res += "string";
		break;
	}
	if (myDepth > 0){
		for (size_t i = 0 ; i < myDepth ; i++){
			res += "@";
		}
	}
	return res;
}

} //End namespace
