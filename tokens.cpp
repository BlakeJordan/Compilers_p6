#include "tokens.hpp"
#include "grammar.hh"
using TokenKind = lake::Parser::token;

namespace lake{
	Token::Token(size_t lineIn, size_t colIn, int kindIn){
		this->_kind = kindIn;
		this->_line = lineIn;
		this->_column = colIn;
	}

	int Token::kind(){
		return _kind;
	}

	IDToken::IDToken(size_t ll, size_t cc, std::string value)
	: Token(ll,cc,TokenKind::ID){
		this->_value = value;
	}

	IntLitToken::IntLitToken(size_t ll, size_t cc, int value)
	: Token(ll,cc,TokenKind::INTLITERAL){
		this->_value = value;
	}
	StringLitToken::StringLitToken(size_t ll, size_t cc, std::string value)
	: Token(ll,cc,TokenKind::STRINGLITERAL)
	{
		this->_value = value;
	}
} // End namespace
