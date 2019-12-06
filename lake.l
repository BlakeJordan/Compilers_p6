%{
#include <string>
#include <limits.h>

/* Provide custom yyFlexScanner subclass and specify the interface */
#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int lake::Scanner::yylex( lake::Parser::semantic_type * const lval )

/* typedef to make the returns for the tokens shorter */
using TokenKind = lake::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( TokenKind::END )

/* Exclude unistd.h for Visual Studio compatability. */
#define YY_NO_UNISTD_H

%}

%option debug
%option nodefault
%option yyclass="lake::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]
WHITESPACE   [\040\t]
LETTER       [a-zA-Z]
ESCAPEDCHAR   [nt'\"?\\]
NOTNEWLINEORESCAPEDCHAR   [^\nnt'\"?\\]
NOTNEWLINEORQUOTE [^\n\"]
NOTNEWLINEORQUOTEORESCAPE [^\n\"\\]


%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

bool		{ return produceNoArgToken(TokenKind::BOOL); }
void		{ return produceNoArgToken(TokenKind::VOID); }
int		{ return produceNoArgToken(TokenKind::INT); }
true		{ return produceNoArgToken(TokenKind::TRUE); }
false		{ return produceNoArgToken(TokenKind::FALSE); }
if		{ return produceNoArgToken(TokenKind::IF); }
else		{ return produceNoArgToken(TokenKind::ELSE); }
while		{ return produceNoArgToken(TokenKind::WHILE); }
return		{ return produceNoArgToken(TokenKind::RETURN); }
"{"		{ return produceNoArgToken(TokenKind::LCURLY); }
"}"		{ return produceNoArgToken(TokenKind::RCURLY); }
"@"		{ return produceNoArgToken(TokenKind::DEREF); }
"("		{ return produceNoArgToken(TokenKind::LPAREN); }
")"		{ return produceNoArgToken(TokenKind::RPAREN); }
";"		{ return produceNoArgToken(TokenKind::SEMICOLON); }
","		{ return produceNoArgToken(TokenKind::COMMA); }
"write"		{ return produceNoArgToken(TokenKind::WRITE); }
"read"		{ return produceNoArgToken(TokenKind::READ); }
"++"		{ return produceNoArgToken(TokenKind::CROSSCROSS); }
"--"		{ return produceNoArgToken(TokenKind::DASHDASH); }
"+"		{ return produceNoArgToken(TokenKind::CROSS); }
"-"		{ return produceNoArgToken(TokenKind::DASH); }
"*"		{ return produceNoArgToken(TokenKind::STAR); }
"/"		{ return produceNoArgToken(TokenKind::SLASH); }
"!"		{ return produceNoArgToken(TokenKind::NOT); }
"&&"		{ return produceNoArgToken(TokenKind::AND); }
"||"		{ return produceNoArgToken(TokenKind::OR); }
"=="		{ return produceNoArgToken(TokenKind::EQUALS); }
"!="		{ return produceNoArgToken(TokenKind::NOTEQUALS); }
"<"		{ return produceNoArgToken(TokenKind::LESS); }
">"		{ return produceNoArgToken(TokenKind::GREATER); }
"<="		{ return produceNoArgToken(TokenKind::LESSEQ); }
">="		{ return produceNoArgToken(TokenKind::GREATEREQ); }
"="		{ return produceNoArgToken(TokenKind::ASSIGN); }
({LETTER}|_)({LETTER}|{DIGIT}|_)*		{
               yylval->tokenValue = new IDToken(lineNum, charNum, yytext);
		charNum += yyleng;
               return TokenKind::ID;
		}

{DIGIT}+	{
		double overflow = std::stod(yytext);
		int intVal = atoi(yytext);
		if (overflow > INT_MAX){
			std::string msg = "Integer literal too large;"
			" using max value";
			warn(0, 0, msg);
			intVal = INT_MAX;
		}
                yylval->tokenValue = new IntLitToken(lineNum, charNum, intVal);
		charNum += yyleng;
                return TokenKind::INTLITERAL;

		}

\"({NOTNEWLINEORQUOTEORESCAPE}|\\{ESCAPEDCHAR})*\" {
		yylval->tokenValue = new StringLitToken(lineNum, charNum, yytext);
		charNum += yyleng;
		return TokenKind::STRINGLITERAL;
          }

\"({NOTNEWLINEORQUOTEORESCAPE}|\\{ESCAPEDCHAR})* {
		// unterminated string
		error(lineNum, charNum, "unterminated string literal ignored");
		charNum += yyleng;
          }

\"({NOTNEWLINEORQUOTEORESCAPE}|\\{ESCAPEDCHAR})*\\{NOTNEWLINEORESCAPEDCHAR}({NOTNEWLINEORQUOTE})*\" {
		// bad escape character
		error(lineNum, charNum, "string literal with bad escaped character ignored");
		charNum += yyleng;
          }

\"({NOTNEWLINEORQUOTEORESCAPE}|\\{ESCAPEDCHAR})*(\\{NOTNEWLINEORESCAPEDCHAR})?({NOTNEWLINEORQUOTEORESCAPE}|\\{ESCAPEDCHAR})*\\? {
		// bad escape character
		std::string msg = "unterminated string literal with bad"
		" escaped character ignored";
		error(lineNum, charNum, msg);
		charNum += yyleng;
          }

\n|(\r\n)   {
		lineNum++;
		charNum = 1;
            }


[ \t]+	    {
		charNum += yyleng;
	    }

("//"|"#")[^\n]*	{
		//Comment. Ignore. Don't need to update char num
		// since everything up to end of line will never by
		// part of a report
	    	}



.           {
		std::string msg = "Illegal character ";
		msg += yytext;
		error(lineNum,charNum,msg);
		charNum += yyleng;
            }
%%
