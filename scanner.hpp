#ifndef __LAKE_SCANNER_HPP__
#define __LAKE_SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "grammar.hh"

namespace lake{

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in)
   {
	lineNum = 1;
	charNum = 1;
   };
   virtual ~Scanner() {
   };

   //get rid of override virtual function warning
   using FlexLexer::yylex;

   // YY_DECL defined in the flex lake.l
   virtual
   int yylex( lake::Parser::semantic_type * const lval);

   void warn(int lineNumIn, int charNumIn, std::string msg){
	std::cerr << lineNumIn << ":" << charNumIn 
		<< " ***WARNING*** " << msg << std::endl;
   }

   void error(int lineNumIn, int charNumIn, std::string msg){
	std::cerr << lineNumIn << ":" << charNumIn 
		<< " ***ERROR*** " << msg << std::endl;
   }

   /* Convenience function to create a token with no
	"arguments" (i.e. a token that need not store
	the value it represents) and update the 
	scanner state (i.e. the lineNum and charNum)
	Most tokens are NoArg so this function avoids a lot 
	of copy-paste in the .l file.
   */
   int produceNoArgToken(int tagIn){
        this->yylval->tokenValue = new NoArgToken(
	  this->lineNum, this->charNum, tagIn);
        charNum += static_cast<size_t>(yyleng);
        return tagIn;
   }

   void outputTokens(std::ostream& outstream);

private:
   /* yyval ptr */
   lake::Parser::semantic_type *yylval = nullptr;
   size_t lineNum;
   size_t charNum;
};

} /* end namespace */

#endif /* END __TEENC_SCANNER_HPP__ */
