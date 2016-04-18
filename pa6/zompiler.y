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
%token <token> TMAIN TROTATE TFORWARD TBOOLEAN TIF TELSE TATTACK TRANGED TISHUMAN TISZOMBIE TISPASSABLE TISRANDOM TISWALL

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate attack ranged ifelse forward is_zombie is_human is_passable is_random is_wall
 
/* Expressions */
%type <numeric> numeric

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl; 
											($3)->SetMainBlock(); 
											g_MainBlock = $3;
											 }
;

block		: statement { std::cout << "Single statement" << std::endl; $$ = new NBlock(); ($$)->AddStatement($1); }
				| block statement {
				 std::cout << "Multiple statements" << std::endl; 
				  ($1)->AddStatement($2);
				 } 
/* TODO: Add support for multiple statements in a block */
;

statement	: rotate TSEMI  | ifelse  | bool TSEMI | attack TSEMI | bool | ranged TSEMI | forward TSEMI | is_zombie | is_human| is_passable | is_random  | is_wall
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl;
												$$ = new NRotate($3); }
;

numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl; 
						$$ = new NNumeric(*($1));}
;
ifelse		: TIF TLPAREN bool TRPAREN {std::cout << "IF command" << std::endl; } TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE  { std::cout << "If ELSE statement" << std::endl;}
;
bool		:  is_zombie | is_human| is_passable | is_random  | is_wall
;
attack		: TATTACK TLPAREN TRPAREN   { std::cout << "ATTACK command" << std::endl;
											$$ = new NAttack(); }
;
ranged		: TRANGED TLPAREN TRPAREN   { std::cout << "RANGED ATTACK command" << std::endl;
											$$= new NRangedAttack(); }
;
is_zombie	: TISZOMBIE TLPAREN numeric TRPAREN {$$ = new Is_Zombie($3);}
;
is_human	: TISHUMAN TLPAREN numeric TRPAREN  {$$ = new Is_Human($3);}
;
is_passable : TISPASSABLE TLPAREN TRPAREN		{$$ = new Is_Passable();}
;
is_random	: TISRANDOM TLPAREN TRPAREN			{$$ = new Is_Random();}
;
is_wall		: TISWALL TLPAREN TRPAREN			{$$ = new Is_Wall(); }
;
forward		: TFORWARD TLPAREN TRPAREN { $$= new NForward();}
;
%%
