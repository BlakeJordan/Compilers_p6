#include <fstream>
#include "scanner.hpp"

using namespace lake;

using TokenKind = lake::Parser::token;
using Lexeme = lake::Parser::semantic_type;

void lake::Scanner::outputTokens( std::ostream& out )
{
   Lexeme lexeme;
   int tokenTag;
   while(true){
   	tokenTag = this->yylex(&lexeme);
	switch (tokenTag){
		case TokenKind::END:
			out << "EOF" << std::endl;
			return;
		case TokenKind::BOOL:
			out << "bool" << std::endl;
			break;
		case TokenKind::INT:
			out << "int" << std::endl;
			break;
		case TokenKind::VOID:
			out << "void" << std::endl;
			break;
		case TokenKind::TRUE:
			out << "true" << std::endl;
			break;
		case TokenKind::FALSE:
			out << "false" << std::endl;
			break;
		case TokenKind::IF:
			out << "if" << std::endl;
			break;
		case TokenKind::ELSE:
			out << "else" << std::endl;
			break;
		case TokenKind::WHILE:
			out << "while" << std::endl;
			break;
		case TokenKind::RETURN:
			out << "return" << std::endl;
			break;
		case TokenKind::ID:
			{
			IDToken * tok = static_cast<IDToken *>(
				lexeme.tokenValue);
			out << "ID:" << tok->value() << std::endl;
			break;
			}
		case TokenKind::INTLITERAL:
			{
			IntLitToken * tok = static_cast<IntLitToken *>(
				lexeme.tokenValue);
			out << "INTLIT:" << tok->value() << std::endl;	
			break;
			}
		case TokenKind::STRINGLITERAL:
			{
			StringLitToken * tok = static_cast<StringLitToken *>(
				lexeme.tokenValue);
			out << "STRINGLIT:" << tok->value() << std::endl;	
			break;
			}
		case TokenKind::LBRACE:
			out << "[" << std::endl;
			break;
		case TokenKind::RBRACE:
			out << "]" << std::endl;
			break;
		case TokenKind::LCURLY:
			out << "{" << std::endl;
			break;
		case TokenKind::RCURLY:
			out << "}" << std::endl;
			break;
		case TokenKind::LPAREN:
			out << "(" << std::endl;
			break;
		case TokenKind::RPAREN:
			out << ")" << std::endl;
			break;
		case TokenKind::SEMICOLON:
			out << ";" << std::endl;
			break;
		case TokenKind::COMMA:
			out << "," << std::endl;
			break;
		case TokenKind::WRITE:
			out << "<<" << std::endl;
			break;
		case TokenKind::READ:
			out << ">>" << std::endl;
			break;
		case TokenKind::CROSSCROSS:
			out << "++" << std::endl;
			break;
		case TokenKind::DASHDASH:
			out << "--" << std::endl;
			break;
		case TokenKind::CROSS:
			out << "+" << std::endl;
			break;
		case TokenKind::DASH:
			out << "-" << std::endl;
			break;
		case TokenKind::STAR:
			out << "*" << std::endl;
			break;
		case TokenKind::SLASH:
			out << "/" << std::endl;
			break;
		case TokenKind::NOT:
			out << "!" << std::endl;
			break;
		case TokenKind::AND:
			out << "&&" << std::endl;
			break;
		case TokenKind::OR:
			out << "||" << std::endl;
			break;
		case TokenKind::EQUALS:
			out << "==" << std::endl;
			break;
		case TokenKind::NOTEQUALS:
			out << "!=" << std::endl;
			break;
		case TokenKind::LESS:
			out << "<" << std::endl;
			break;
		case TokenKind::GREATER:
			out << ">" << std::endl;
			break;
		case TokenKind::LESSEQ:
			out << "<=" << std::endl;
			break;
		case TokenKind::GREATEREQ:
			out << ">=" << std::endl;
			break;
		case TokenKind::ASSIGN:
			out << "=" << std::endl;
			break;
		case TokenKind::DEREF:
			out << "@" << std::endl;
			break;
		case TokenKind::REF:
			out << "^" << std::endl;
			break;
		default:
			out << "UNKNOWN TOKEN" << std::endl;
			break;
	}
   }
}
