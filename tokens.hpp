#ifndef TEENC_TOKEN_H
#define TEENC_TOKEN_H

#include <iostream>

namespace lake{

class Token {
	public:
		Token(size_t lineIn, size_t columnIn, int kind);
		int kind();
		size_t _line;
		size_t _column;

	protected:
		int _kind;
};

class NoArgToken : public Token {
	public:
		NoArgToken(size_t liIn, size_t colIn, int tag) 
		: Token(liIn,colIn,tag) { };
		
};

class IntLitToken : public Token {
	public:
		IntLitToken(size_t line, size_t col, int value);
		int value() { return _value; }
	private:
		int _value;
};

class IDToken : public Token {
	public:
		IDToken(size_t line, size_t col, std::string id);
		std::string value() { return _value; }
	private:
		std::string _value;
};

class StringLitToken : public Token {
	public:
		StringLitToken(size_t line, size_t col, std::string value);
		std::string value() { return _value; }
	private:
		std::string _value;
};

} //End namespace

#endif
