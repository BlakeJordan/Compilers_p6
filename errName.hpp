#ifndef TEENC_NAME_ERROR_REPORTING_HH
#define TEENC_NAME_ERROR_REPORTING_HH

#include "err.hpp"

namespace lake{

class NameErr{
public:
static bool undecl(size_t line, size_t col){
	Err::semanticReport(line, col, "Undeclared identifier");
	return false;
}
static bool multiDecl(size_t line, size_t col){
	Err::semanticReport(line, col, "Multiply declared identifier");
	return false;
}
static bool badPointer(size_t line, size_t col){
	Err::semanticReport(line, col, "Invalid pointer type");
	return false;
}
static bool badVoid(size_t line, size_t col){
	Err::semanticReport(line, col, "Non-function declared void");
	return false;
}
};

} //End namespace lake

#endif
