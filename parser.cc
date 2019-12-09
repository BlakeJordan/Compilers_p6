// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "grammar.hh"

// User implementation prologue.

#line 51 "parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 33 "lake.yy" // lalr1.cc:413

   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for interoperation between scanner/parser */
   #include "scanner.hpp"

#undef yylex
#define yylex scanner.yylex

#line 65 "parser.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "lake.yy" // lalr1.cc:479
namespace lake {
#line 132 "parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (lake::Scanner  &scanner_yyarg, lake::ProgramNode** root_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 160 "lake.yy" // lalr1.cc:859
    {
          (yylhs.value.programNode) = new ProgramNode(new DeclListNode((yystack_[0].value.declList)));
          *root = (yylhs.value.programNode);
          }
#line 601 "parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 166 "lake.yy" // lalr1.cc:859
    {
           (yystack_[1].value.declList)->push_back((yystack_[0].value.declNode));
           (yylhs.value.declList) = (yystack_[1].value.declList);
           }
#line 610 "parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 171 "lake.yy" // lalr1.cc:859
    {
           (yylhs.value.declList) = new std::list<DeclNode *>();
           }
#line 618 "parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 175 "lake.yy" // lalr1.cc:859
    { (yylhs.value.declNode) = (yystack_[0].value.varDeclNode); }
#line 624 "parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 176 "lake.yy" // lalr1.cc:859
    { (yylhs.value.declNode) = (yystack_[0].value.fnDecl); }
#line 630 "parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 178 "lake.yy" // lalr1.cc:859
    { (yylhs.value.varDeclList) = (yystack_[1].value.varDeclList); (yylhs.value.varDeclList)->push_back((yystack_[0].value.varDeclNode)); }
#line 636 "parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 179 "lake.yy" // lalr1.cc:859
    { (yylhs.value.varDeclList) = new std::list<VarDeclNode *>(); }
#line 642 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 182 "lake.yy" // lalr1.cc:859
    { (yylhs.value.varDeclNode) = new VarDeclNode((yystack_[2].value.typeNode), (yystack_[1].value.idNode)); }
#line 648 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 185 "lake.yy" // lalr1.cc:859
    { (yylhs.value.fnDecl) = new FnDeclNode((yystack_[3].value.typeNode), (yystack_[2].value.idNode), (yystack_[1].value.formalsType), (yystack_[0].value.fnBody)); }
#line 654 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 188 "lake.yy" // lalr1.cc:859
    { (yylhs.value.formalsType) = new FormalsListNode(new std::list<FormalDeclNode *>()); }
#line 660 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 190 "lake.yy" // lalr1.cc:859
    { (yylhs.value.formalsType) = new FormalsListNode((yystack_[1].value.formalsList)); }
#line 666 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 193 "lake.yy" // lalr1.cc:859
    {
              std::list<FormalDeclNode *> * list = new std::list<FormalDeclNode *>();
              list->push_back((yystack_[0].value.formalDecl));
              (yylhs.value.formalsList) = list;
              }
#line 676 "parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 199 "lake.yy" // lalr1.cc:859
    {
              (yystack_[0].value.formalsList)->push_front((yystack_[2].value.formalDecl));
              (yylhs.value.formalsList) = (yystack_[0].value.formalsList);
              }
#line 685 "parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 204 "lake.yy" // lalr1.cc:859
    {
         (yylhs.value.fnBody) = new FnBodyNode((yystack_[3].value.tokenValue)->_line, (yystack_[3].value.tokenValue)->_column, 
		new VarDeclListNode((yystack_[2].value.varDeclList)), new StmtListNode((yystack_[1].value.stmtList)));
       }
#line 694 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 210 "lake.yy" // lalr1.cc:859
    { (yylhs.value.formalDecl) = new FormalDeclNode((yystack_[1].value.typeNode), (yystack_[0].value.idNode)); }
#line 700 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 213 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtList) = new std::list<StmtNode *>(); }
#line 706 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 215 "lake.yy" // lalr1.cc:859
    { 
           (yystack_[1].value.stmtList)->push_back((yystack_[0].value.stmtNode));
           (yylhs.value.stmtList) = (yystack_[1].value.stmtList);
           }
#line 715 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 220 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new AssignStmtNode((yystack_[1].value.assignNode)); }
#line 721 "parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 221 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new PostIncStmtNode((yystack_[2].value.exp)); }
#line 727 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 222 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new PostDecStmtNode((yystack_[2].value.exp)); }
#line 733 "parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 223 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new ReadStmtNode((yystack_[1].value.exp)); }
#line 739 "parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 224 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new WriteStmtNode((yystack_[1].value.exp)); }
#line 745 "parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 226 "lake.yy" // lalr1.cc:859
    { 
        (yylhs.value.stmtNode) = new IfStmtNode((yystack_[7].value.tokenValue)->_line, (yystack_[7].value.tokenValue)->_column, (yystack_[5].value.exp), 
		new VarDeclListNode((yystack_[2].value.varDeclList)),
		new StmtListNode((yystack_[1].value.stmtList))
	);
        }
#line 756 "parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 233 "lake.yy" // lalr1.cc:859
    { 
        (yylhs.value.stmtNode) = new IfElseStmtNode(
                (yystack_[10].value.exp), 
                new VarDeclListNode((yystack_[7].value.varDeclList)), 
                new StmtListNode((yystack_[6].value.stmtList)), 
                new VarDeclListNode((yystack_[2].value.varDeclList)),
                new StmtListNode((yystack_[1].value.stmtList))
	); 
        }
#line 770 "parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 243 "lake.yy" // lalr1.cc:859
    { 
        (yylhs.value.stmtNode) = new WhileStmtNode((yystack_[7].value.tokenValue)->_line, (yystack_[7].value.tokenValue)->_column, (yystack_[5].value.exp), 
		new VarDeclListNode((yystack_[2].value.varDeclList)), new StmtListNode((yystack_[1].value.stmtList))); 
       }
#line 779 "parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 248 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new ReturnStmtNode((yystack_[2].value.tokenValue)->_line, (yystack_[2].value.tokenValue)->_column, (yystack_[1].value.exp)); }
#line 785 "parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 250 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new ReturnStmtNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, nullptr); }
#line 791 "parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 251 "lake.yy" // lalr1.cc:859
    { (yylhs.value.stmtNode) = new CallStmtNode((yystack_[1].value.callNode)); }
#line 797 "parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 255 "lake.yy" // lalr1.cc:859
    { (yylhs.value.assignNode) = new AssignNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 803 "parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 258 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[0].value.assignNode); }
#line 809 "parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new PlusNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 815 "parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new MinusNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 821 "parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 264 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new TimesNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 827 "parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 266 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new DivideNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 833 "parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 268 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new NotNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[0].value.exp)); }
#line 839 "parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 270 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new AndNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 845 "parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 272 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new OrNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 851 "parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 274 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new EqualsNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 857 "parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 276 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new NotEqualsNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 863 "parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 278 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new LessNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 869 "parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 280 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new GreaterNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 875 "parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 282 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new LessEqNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 881 "parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 284 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new GreaterEqNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 887 "parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 285 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new UnaryMinusNode((yystack_[0].value.exp)); }
#line 893 "parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 286 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 899 "parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 288 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 905 "parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 289 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new IntLitNode((yystack_[0].value.intTokenValue)); }
#line 911 "parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 290 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new StrLitNode((yystack_[0].value.strTokenValue)); }
#line 917 "parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 291 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new TrueNode((yystack_[0].value.tokenValue)->_line, (yystack_[0].value.tokenValue)->_column); }
#line 923 "parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 292 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new FalseNode((yystack_[0].value.tokenValue)->_line, (yystack_[0].value.tokenValue)->_column); }
#line 929 "parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 293 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[1].value.exp); }
#line 935 "parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 294 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[0].value.callNode); }
#line 941 "parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 297 "lake.yy" // lalr1.cc:859
    { 
        (yylhs.value.callNode) = new CallExpNode((yystack_[2].value.idNode), new ExpListNode(new std::list<ExpNode *>()));
        }
#line 949 "parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 301 "lake.yy" // lalr1.cc:859
    { 
        (yylhs.value.callNode) = new CallExpNode((yystack_[3].value.idNode), new ExpListNode((yystack_[1].value.expList))); 
        }
#line 957 "parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 306 "lake.yy" // lalr1.cc:859
    { 
        std::list<ExpNode *> * list = new std::list<ExpNode *>();
        list->push_back((yystack_[0].value.exp));
        (yylhs.value.expList) = list;
        }
#line 967 "parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 312 "lake.yy" // lalr1.cc:859
    {
        (yystack_[2].value.expList)->push_back((yystack_[0].value.exp));
        (yylhs.value.expList) = (yystack_[2].value.expList);
        }
#line 976 "parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 318 "lake.yy" // lalr1.cc:859
    {
	(yylhs.value.typeNode) = (yystack_[1].value.typeNode);
	(yylhs.value.typeNode)->setPtrDepth((yystack_[0].value.counterTrans));
	}
#line 985 "parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 323 "lake.yy" // lalr1.cc:859
    { (yylhs.value.typeNode) = new IntNode((yystack_[0].value.tokenValue)->_line, (yystack_[0].value.tokenValue)->_column); }
#line 991 "parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 324 "lake.yy" // lalr1.cc:859
    { (yylhs.value.typeNode) = new BoolNode((yystack_[0].value.tokenValue)->_line, (yystack_[0].value.tokenValue)->_column); }
#line 997 "parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 325 "lake.yy" // lalr1.cc:859
    { (yylhs.value.typeNode) = new VoidNode((yystack_[0].value.tokenValue)->_line, (yystack_[0].value.tokenValue)->_column); }
#line 1003 "parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 328 "lake.yy" // lalr1.cc:859
    { (yylhs.value.counterTrans) = (yystack_[0].value.counterTrans) + 1; }
#line 1009 "parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 329 "lake.yy" // lalr1.cc:859
    { (yylhs.value.counterTrans) = 0; }
#line 1015 "parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 331 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = (yystack_[0].value.idNode); }
#line 1021 "parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 332 "lake.yy" // lalr1.cc:859
    { (yylhs.value.exp) = new DerefNode((yystack_[1].value.tokenValue)->_line, (yystack_[1].value.tokenValue)->_column, (yystack_[0].value.exp)); }
#line 1027 "parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 334 "lake.yy" // lalr1.cc:859
    { (yylhs.value.idNode) = new IdNode((yystack_[0].value.idTokenValue)); }
#line 1033 "parser.cc" // lalr1.cc:859
    break;


#line 1037 "parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -97;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     -97,     5,    54,   -97,   -97,   -97,   -97,   -97,   -97,   -97,
       2,     6,   -97,    -4,     6,   -97,    21,   -97,    20,   -97,
     -97,    22,    41,     2,   -97,   -97,   -97,    54,   -97,    54,
     -97,   -97,    56,     2,    53,    66,    48,   -97,   103,    -7,
      -7,   -97,    50,    52,   -14,    67,    64,   103,   103,   -97,
     -97,   -97,   -97,   103,   -97,   128,   103,   -97,   223,   -97,
     -97,    45,   244,    73,   -97,   -97,   -97,   -97,    75,    77,
     103,    94,   125,   149,   164,   -97,   -97,   -97,   -97,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   -97,   -97,   -97,   -97,   259,   -97,   259,    12,    87,
      88,   -97,    24,    24,   -97,   -97,   289,   274,   304,   304,
     304,   304,   304,   304,   -97,   103,   -97,   -97,   259,    54,
      54,   198,   207,    95,   -97,    90,   -97,    54,   224,   -97
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    60,    59,    61,     3,     5,     6,
       0,    63,    66,     0,    63,    58,     0,     9,     0,    62,
      11,     0,    13,     0,     8,    10,    12,     0,    16,    17,
      14,     7,     0,     0,     0,     0,     0,    15,     0,     0,
       0,    18,     0,     0,     0,    64,     0,     0,     0,    50,
      51,    48,    49,     0,    28,     0,     0,    31,     0,    46,
      53,    47,     0,     0,    64,    65,    19,    29,     0,     0,
       0,     0,     0,     0,     0,    45,    47,    36,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    22,    20,    21,    30,    54,    56,     0,     0,
       0,    52,    32,    33,    34,    35,    37,    38,    39,    40,
      41,    42,    43,    44,    55,     0,     8,     8,    57,    17,
      17,     0,     0,    24,    26,     0,     8,    17,     0,    25
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -97,   -97,   -97,   -97,   -96,   112,   -97,   -97,    92,   -97,
     -97,   -44,   -97,   -30,   -37,    60,   -28,   -97,     1,   -97,
     106,   -32,    -1
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,    29,    31,     9,    18,    21,    25,
      22,    32,    41,    57,    58,    59,    60,    98,    33,    11,
      15,    61,    45
  };

  const short int
  Parser::yytable_[] =
  {
      44,    62,    42,    10,    43,     3,    12,    63,    65,    13,
      72,    73,    68,    69,    16,    12,    74,    23,    17,    77,
     119,   120,    28,    76,    40,     4,     5,     6,    23,    70,
     127,   114,    46,    95,    97,   115,    24,    14,    64,    64,
      20,    26,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    81,    49,    50,    82,     4,     5,
       6,    12,    51,    52,    27,    34,    53,    35,    36,    12,
      54,    47,    66,    37,    67,   121,   122,    55,   118,    40,
      38,    39,    56,   128,    48,    71,    17,    40,    70,    44,
      44,    42,    42,    43,    43,    92,    44,    93,    42,    94,
      43,    49,    50,   116,   117,   125,   126,    12,    51,    52,
      49,    50,    53,    96,     8,    75,    12,    51,    52,    30,
      19,    53,     0,    55,     0,    40,     0,     0,    56,     0,
       0,     0,    55,     0,    40,    49,    50,    56,     0,     0,
       0,    12,    51,    52,    99,     0,    53,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,    82,    40,
      83,    84,    85,    86,    87,    88,    89,    90,   100,     0,
       0,     0,     0,     0,     0,     0,     0,    79,    80,    81,
       0,     0,    82,   101,    83,    84,    85,    86,    87,    88,
      89,    90,    79,    80,    81,     0,     0,    82,     0,    83,
      84,    85,    86,    87,    88,    89,    90,    34,     0,    35,
      36,    12,     0,     0,     0,   123,    34,     0,    35,    36,
      12,     0,    38,    39,   124,     0,     0,     0,     0,    40,
       0,    38,    39,    34,     0,    35,    36,    12,    40,     0,
       0,   129,     0,     0,     0,    78,     0,     0,    38,    39,
       0,    79,    80,    81,     0,    40,    82,     0,    83,    84,
      85,    86,    87,    88,    89,    90,    91,     0,     0,     0,
       0,     0,    79,    80,    81,     0,     0,    82,     0,    83,
      84,    85,    86,    87,    88,    89,    90,    79,    80,    81,
       0,     0,    82,     0,    83,    84,    85,    86,    87,    88,
      89,    90,    79,    80,    81,     0,     0,    82,     0,    83,
       0,    85,    86,    87,    88,    89,    90,    79,    80,    81,
       0,     0,    82,     0,     0,     0,    85,    86,    87,    88,
      89,    90,    79,    80,    81,     0,     0,    82,     0,     0,
       0,    -1,    -1,    -1,    -1,    -1,    -1
  };

  const short int
  Parser::yycheck_[] =
  {
      32,    38,    32,     2,    32,     0,    13,    39,    40,    10,
      47,    48,    26,    27,    18,    13,    53,    16,    22,    56,
     116,   117,    23,    55,    31,     4,     5,     6,    27,    43,
     126,    19,    33,    70,    71,    23,    16,    31,    39,    40,
      19,    19,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    30,     7,     8,    33,     4,     5,
       6,    13,    14,    15,    23,     9,    18,    11,    12,    13,
      22,    18,    22,    17,    22,   119,   120,    29,   115,    31,
      24,    25,    34,   127,    18,    18,    22,    31,    43,   121,
     122,   121,   122,   121,   122,    22,   128,    22,   128,    22,
     128,     7,     8,    16,    16,    10,    16,    13,    14,    15,
       7,     8,    18,    19,     2,    55,    13,    14,    15,    27,
      14,    18,    -1,    29,    -1,    31,    -1,    -1,    34,    -1,
      -1,    -1,    29,    -1,    31,     7,     8,    34,    -1,    -1,
      -1,    13,    14,    15,    19,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    -1,    33,    31,
      35,    36,    37,    38,    39,    40,    41,    42,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    -1,    33,    19,    35,    36,    37,    38,    39,    40,
      41,    42,    28,    29,    30,    -1,    -1,    33,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,     9,    -1,    11,
      12,    13,    -1,    -1,    -1,    17,     9,    -1,    11,    12,
      13,    -1,    24,    25,    17,    -1,    -1,    -1,    -1,    31,
      -1,    24,    25,     9,    -1,    11,    12,    13,    31,    -1,
      -1,    17,    -1,    -1,    -1,    22,    -1,    -1,    24,    25,
      -1,    28,    29,    30,    -1,    31,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    28,    29,    30,
      -1,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    28,    29,    30,    -1,    -1,    33,    -1,    35,
      -1,    37,    38,    39,    40,    41,    42,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    45,    46,     0,     4,     5,     6,    47,    49,    50,
      62,    63,    13,    66,    31,    64,    18,    22,    51,    64,
      19,    52,    54,    62,    16,    53,    19,    23,    66,    48,
      52,    49,    55,    62,     9,    11,    12,    17,    24,    25,
      31,    56,    57,    60,    65,    66,    66,    18,    18,     7,
       8,    14,    15,    18,    22,    29,    34,    57,    58,    59,
      60,    65,    58,    65,    66,    65,    22,    22,    26,    27,
      43,    18,    58,    58,    58,    59,    65,    58,    22,    28,
      29,    30,    33,    35,    36,    37,    38,    39,    40,    41,
      42,    22,    22,    22,    22,    58,    19,    58,    61,    19,
      19,    19,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    19,    23,    16,    16,    58,    48,
      48,    55,    55,    17,    17,    10,    16,    48,    55,    17
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      50,    51,    51,    52,    52,    53,    54,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    60,    60,    61,    61,    62,    63,
      63,    63,    64,    64,    65,    65,    66
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     1,     1,     2,     0,     3,
       4,     2,     3,     1,     3,     4,     2,     0,     2,     2,
       3,     3,     3,     3,     8,    13,     8,     3,     2,     2,
       3,     1,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     4,     1,     3,     2,     1,
       1,     1,     2,     0,     1,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "CHAR", "BOOL", "INT", "VOID",
  "TRUE", "FALSE", "IF", "ELSE", "WHILE", "RETURN", "ID", "INTLITERAL",
  "STRINGLITERAL", "LCURLY", "RCURLY", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "SEMICOLON", "COMMA", "WRITE", "READ", "CROSSCROSS",
  "DASHDASH", "CROSS", "DASH", "STAR", "DEREF", "REF", "SLASH", "NOT",
  "AND", "OR", "EQUALS", "NOTEQUALS", "LESS", "GREATER", "LESSEQ",
  "GREATEREQ", "ASSIGN", "$accept", "program", "declList", "decl",
  "varDeclList", "varDecl", "fnDecl", "formals", "formalsList", "fnBody",
  "formalDecl", "stmtList", "stmt", "assignExp", "exp", "term", "fncall",
  "actualList", "type", "primtype", "ptrdepth", "loc", "id", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   159,   159,   165,   171,   175,   176,   178,   179,   181,
     184,   187,   189,   192,   198,   204,   209,   213,   214,   220,
     221,   222,   223,   224,   225,   232,   242,   247,   249,   251,
     254,   257,   259,   261,   263,   265,   267,   269,   271,   273,
     275,   277,   279,   281,   283,   285,   286,   288,   289,   290,
     291,   292,   293,   294,   296,   300,   305,   311,   317,   323,
     324,   325,   328,   329,   331,   332,   334
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
    };
    const unsigned int user_token_number_max_ = 298;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "lake.yy" // lalr1.cc:1167
} // lake
#line 1579 "parser.cc" // lalr1.cc:1167
#line 336 "lake.yy" // lalr1.cc:1168

void
lake::Parser::error(const std::string & err_msg)
{
   lake::Err::syntaxReport(err_msg);
}
