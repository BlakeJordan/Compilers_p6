#ifndef TEENC_TYPE_ERROR_REPORTING_HH
#define TEENC_TYPE_ERROR_REPORTING_HH

#include "err.hpp"

namespace lake{

class TypeErr {
public:
static void writeFn(size_t line, size_t col){
	Err::semanticReport(line, col, "Attempt to write a function");
}
static void writePtr(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Attempt to write a raw pointer");
}
static void writeVoid(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Attempt to write void");
}
static void readFn(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Attempt to read a function");
}
static void readPtr(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Attempt to read an array variable");
}
static void callNonFn(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Attempt to call a non-function");
}
static void badArgCount(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Function call with wrong number of args");
}
static void badArgType(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Type of actual does not match type of formal");
}
static bool missRetValue(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Missing return value");
	return false;
}
static bool extraRetValue(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Return with a value in void function");
	return false;
}
static void badRetValue(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Bad return value");
}
static void badMath(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Arithmetic operator applied to non-numeric operand");
}
static void badRelation(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Relational operator applied to non-numeric operand");
}
static void badLogic(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Logical operator applied to non-bool operand");
}
static void badIf(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Non-bool expression used as an if condition");
}
static void badWhile(size_t line, size_t col){
	Err::semanticReport(line, col, 
	  "Non-bool expression used as a while condition");
}
static void mismatch(size_t line, size_t col){
	Err::semanticReport(line, col, "Type mismatch");
}
static void voidEq(size_t line, size_t col){
	Err::semanticReport(line, col, 
		"Equality operator applied" " to void functions");
}
static void fnEq(size_t line, size_t col){
	Err::semanticReport(line, col, 
		"Equality operator applied to functions");
}
static void arrEq(size_t line, size_t col){
	Err::semanticReport(line, col, 
		"Equality operator applied to arrays");
}
static void fnAssign(size_t line, size_t col){
	Err::semanticReport(line, col, "Function assignment");
}
static void arrAssign(size_t line, size_t col){
	Err::semanticReport(line, col, "Array variable assignment");
}
static void badDeref(size_t line, size_t col){
	Err::semanticReport(line, col, "Invalid operand for dereference");
}

};

} //End namespace lake

#endif
