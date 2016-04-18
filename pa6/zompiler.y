%{
#include "node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

%error-verbose

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN
%token <token> TMAIN TROTATE TFORWARD TBOOLEAN TIF TELSE TATTACK TRANGED

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate attack ranged else if
 
/* Expressions */
%type <numeric> numeric

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl; }
;

block		: statement { std::cout << "Single statement" << std::endl; }
				| block statement { std::cout << "Multiple statements" << std::endl; } 
/* TODO: Add support for multiple statements in a block */
;

statement	: rotate TSEMI  | ifelse  | bool TSEMI | attack TSEMI | bool | ranged TSEMI | forward TSEMI 
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl;
												$$ = new NRotate($3); }
;

numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl; 
						$$ = new NNumeric(*($1));}
;
ifelse		: TIF TLPAREN bool TRPAREN {std::cout << "IF command" << std::endl; } TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE  { std::cout << "If ELSE statement" << std::endl;}
;
bool		: TBOOLEAN TLPAREN TRPAREN  | TBOOLEAN TLPAREN numeric TRPAREN { std::cout << "Boolean command" << std::endl; }
;
attack		: TATTACK TLPAREN TRPAREN   { std::cout << "ATTACK command" << std::endl;
											$$ = new NAttack(); }
;
ranged		: TRANGED TLPAREN TRPAREN   { std::cout << "RANGED ATTACK command" << std::endl;
											$$= new NRangedAttack(); }
;
forward		: TFORWARD TLPAREN TRPAREN {}

%%
