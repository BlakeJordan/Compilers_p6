#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "scanner.hpp"
#include "symbol_table.hpp"
#include "types.hpp"

using namespace lake;

static void usageAndDie(){
	std::cerr << "Usage: lakec <infile> <options>"
	<< " [-t <tokensFile>]"
	<< " [-p <unparseFile>]"
	<< " [-n <nameAnalysisFile>]"
	<< " [-c]"
	<< " [-a <3ACFile>]"
	<< " [-o <x64File>]"
	<< "\n"
	;
	exit(1);
}

static ProgramNode * parse(const char * inFile){
	std::ifstream inStream(inFile);
	if (!inStream.good()){
		std::string msg = "Bad input stream ";
		msg += inFile;
		throw new InternalError(msg.c_str());
	}

	lake::Scanner scanner(&inStream);
	ProgramNode * root = NULL;
	lake::Parser parser(scanner, &root);
	int errCode = parser.parse();
	if (errCode != 0){ return NULL; }

	return root;
}

static void writeAssembly(IRProgram * prog, const char * outPath){

	if (strcmp(outPath, "--") == 0){
		prog->toX64(std::cout);
	} else {
		std::ofstream outStream(outPath);
		if (!outStream.good()){
			std::string msg = "Bad output file " + std::string(outPath);
			throw new InternalError(msg.c_str());
		}
		prog->toX64(outStream);
		outStream.close();
	}


}

static void write3AC(IRProgram * prog, const char * outFile, bool verbose){
	if (outFile == nullptr){
		throw new InternalError("Null 3AC flat file given");
	}
	std::string flatProg = prog->toString(verbose);
	if (strcmp(outFile, "--") == 0){
		std::cout << flatProg << std::endl;
	} else {
		std::ofstream outStream(outFile);
		outStream << flatProg << std::endl;
		outStream.close();
	}
}

static void writeTokenStream(const char * inPath, const char * outPath){
	std::ifstream inStream(inPath);
	if (!inStream.good()){
		std::string msg = "Bad input stream";
		msg += inPath;
		throw new InternalError(msg.c_str());
	}
	if (outPath == nullptr){
		std::string msg = "No tokens output file given";
		throw new InternalError(msg.c_str());
	}

	Scanner scanner(&inStream);
	if (strcmp(outPath, "--") == 0){
		scanner.outputTokens(std::cout);
	} else {
		std::ofstream outStream(outPath);
		if (!outStream.good()){
			std::string msg = "Bad output file ";
			msg += outPath;
			throw new InternalError(msg.c_str());
		}
		scanner.outputTokens(outStream);
		outStream.close();
	}
}

static void unparse(ASTNode * astRoot, const char * outFile){
	if (outFile == nullptr){
		throw new InternalError("Null unparse file given");
	}
	if (strcmp(outFile, "--") == 0){
		astRoot->unparse(std::cout, 0);
	} else {
		std::ofstream outStream(outFile);
		astRoot->unparse(outStream, 0);
		outStream.close();
	}
}

int 
main( const int argc, const char **argv )
{
	if (argc == 0){
		usageAndDie();
	}
	const char * inFile = NULL;
	const char * tokensFile = NULL;
	const char * unparseFile = NULL;
	const char * nameAnalysisFile = NULL;
	bool doTypeChecking = false;
	const char * flattenFile = NULL;
	const char * assemblyFile = NULL;
	bool verbose = false;
	bool useful = false;
	int i = 1;
	for (int i = 1 ; i < argc ; i++){
		if (argv[i][0] == '-'){
			if (argv[i][1] == 't'){
				i++;
				tokensFile = argv[i];
				useful = true;
			} else if (argv[i][1] == 'p'){
				i++;
				unparseFile = argv[i];
				useful = true;
			} else if (argv[i][1] == 'n'){
				i++;
				nameAnalysisFile = argv[i];
				useful = true;
			} else if (argv[i][1] == 'c'){
				i++;
				doTypeChecking = true;
				useful = true;
			} else if (argv[i][1] == 'a'){
				i++;
				flattenFile = argv[i];
				useful = true;
			} else if (argv[i][1] == 'o'){
				i++;
				assemblyFile = argv[i];
				useful = true;
			}
		} else {
			if (inFile == NULL){
				inFile = argv[i];
			} else {
				std::cerr << "Only 1 input file allowed";
				std::cerr << argv[i] << std::endl;
				usageAndDie();
			}
		}
	}
	if (inFile == NULL){
		usageAndDie();
	}
	if (!useful){
		std::cerr << "Whoops, you didn't tell lakec what to do!\n";
		usageAndDie();
	}

	int retCode = 0;

	if (tokensFile != NULL){
		try {
			writeTokenStream(inFile, tokensFile);
		} catch (InternalError * e){
			std::cerr << "Error: " << e->what() << std::endl;
		}
	}

	if (unparseFile != NULL){
		try {
			ASTNode * astRoot = parse(inFile);
			if (astRoot == NULL){
				std::cerr << "Parsing Error\n";
				exit(1);
			}
			unparse(astRoot, unparseFile);
		} catch (ToDoError * e){
			std::cerr << "ToDo: " << e->what() << std::endl;
			exit(1);
		}
	}
	
	if (nameAnalysisFile != NULL){
		try {
			ASTNode * astRoot = parse(inFile);
			if (astRoot == NULL){
				std::cerr << "Parsing Error\n";
				exit(1);
			}
			SymbolTable * symTab = new SymbolTable();
			bool nameAnalysisOk = astRoot->nameAnalysis(symTab);
			if (nameAnalysisOk){
				unparse(astRoot, nameAnalysisFile);
			}
		} catch (ToDoError * e){
			std::cerr << "ToDo: " << e->what() << std::endl;
			exit(1);
		}
	}
	if (doTypeChecking){
		try {
			ProgramNode * astRoot = parse(inFile);
			if (astRoot == NULL){
				std::cerr << "Parsing failed\n";
				exit(1);
			}
			SymbolTable * symTab = new SymbolTable();
			bool nameAnalysisOk = astRoot->nameAnalysis(symTab);
			if (!nameAnalysisOk){
				std::cerr << "Name analysis Failed\n";
				exit(1);
			}

			TypeAnalysis * typeAnalysis = new TypeAnalysis();
			astRoot->typeAnalysis(typeAnalysis);
			if (!typeAnalysis->passed()){
				std::cerr << "Type checking failed\n";
			}
		} catch (ToDoError * e){
			std::cerr << "ToDo: " << e->what() << std::endl;
			exit(1);
		} catch (InternalError * e){
			std::cerr << "Compiler is Broken! " << e->what() << std::endl;
			exit(1);
		}
	}

	if (flattenFile != NULL){
		try {
			ProgramNode * astRoot = parse(inFile);
			if (astRoot == NULL){
				std::cerr << "Parsing Error\n";
				exit(1);
			}
			SymbolTable * symTab = new SymbolTable();
			if (!astRoot->nameAnalysis(symTab)){
				std::cerr << "Name Analysis Error\n";
				exit(1);
			}

			TypeAnalysis * typeAnalysis = new TypeAnalysis();
			astRoot->typeAnalysis(typeAnalysis);
			if (!typeAnalysis->passed()){
				std::cerr << "Type Analysis Error\n";
				exit(1);
			}
			IRProgram * prog = astRoot->to3AC();
			write3AC(prog, flattenFile, verbose);
		} catch (ToDoError * e){
			std::cerr << "ToDo: " << e->what() << std::endl;
			exit(1);
		}
	}

	if (assemblyFile != NULL){
		try {
			ProgramNode * astRoot = parse(inFile);
			if (astRoot == NULL){
				std::cerr << "Parsing Error\n";
				exit(1);
			}
			SymbolTable * symTab = new SymbolTable();
			if (!astRoot->nameAnalysis(symTab)){
				std::cerr << "Name Analysis Error\n";
				exit(1);
			}

			TypeAnalysis * typeAnalysis = new TypeAnalysis();
			astRoot->typeAnalysis(typeAnalysis);
			if (!typeAnalysis->passed()){
				std::cerr << "Type Analysis Error\n";
				exit(1);
			}
			IRProgram * prog = astRoot->to3AC();
			if (prog != NULL){
				writeAssembly(prog, assemblyFile);
			}
		} catch (ToDoError * e){
			std::cerr << "ToDo: " << e->what() << std::endl;
			exit(1);
		}
	}

	return retCode;
}
