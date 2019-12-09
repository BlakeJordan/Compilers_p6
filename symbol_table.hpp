#ifndef LAKE_SYMBOL_TABLE_HPP
#define LAKE_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>
#include "types.hpp"

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using namespace std;

namespace lake{

enum SymbolKind {
	VAR, FN
};

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols 
// exist for the lifetime of a scope in the 
// symbol table. 
class SemSymbol {
public:
	SemSymbol(SymbolKind kindIn, const DataType * typeIn, std::string nameIn) 
	: myKind(kindIn), myType(typeIn), myName(nameIn){
	}
	virtual std::string getTypeString();
	virtual std::string toString();
	std::string getName() const { return myName; }
	SymbolKind getKind() { return myKind; }
	const DataType * getType() { return myType; }
	static std::string kindToString(SymbolKind symKind) { 
		switch(symKind){
			case VAR: return "var";
			case FN: return "fn";
		}
		return "UNKNOWN KIND";
	} 
private:
	SymbolKind myKind;
	const DataType * myType;
	std::string myName;
};

//A single scope. The symbol table is broken down into a 
// chain of scope tables, and each scope table holds 
// semantic symbols for a single scope. For example,
// the globals scope will be represented by a ScopeTable,
// and the contents of each function can be represented by
// a ScopeTable.
class ScopeTable {
	public:
		ScopeTable();
		SemSymbol * lookup(std::string name);
		bool insert(SemSymbol * symbol);
		bool clash(std::string name);
		std::string toString();
	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		ScopeTable * enterScope();
		void leaveScope();
		ScopeTable * getCurrentScope();
		bool insert(SemSymbol * symbol);
		SemSymbol * find(std::string varName);
		bool clash(std::string name);
	private:
		std::list<ScopeTable *> * scopeTableChain;
};

	
}

#endif
