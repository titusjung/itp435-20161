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
%token <token> TMAIN TROTATE

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate
 
/* Expressions */
%type <numeric> numeric

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl; }
;

block		: statement { std::cout << "Single statement" << std::endl; }
/* TODO: Add support for multiple statements in a block */
;

statement	: rotate TSEMI
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl; }
;
			
numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl; }
;

%%
