%{
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For malloc here and in symbol table */
#include "3endload.c"
#include "printer.h"
#include "MIPS.c"

int errors;

void yyerror(const char *str) {
        fprintf(stderr,"error: %s\n",str);
}

extern AST_list *root;
extern AST_list *iterator;
extern Code_list *int_code;
extern Code_list *int_iterator;

%}

%union { 
	int num;
	float flo;
	_Bool boo;
	char *id;
	char *string;
	struct AST *ast;
	struct AST_list *list;
}

%token NUMBER FLOAT BOOLEAN IDENTIFIER
%token STRING
%token IF IN WHILE
%token THEN ELSE DO END
%token INTEGER
%token ASSGNOP
%token PRINTLN NEWLINE
%token EQUALS DIFFER
%token LT GT LET GET
%token NOT

%type <num> NUMBER
%type <flo> FLOAT
%type <boo> BOOLEAN
%type <id> IDENTIFIER
%type <string> STRING
%type <list> explist
%type <ast> exp
%type <ast> println

%start input

%left EQUALS DIFFER
%left LT GT LET GET
%left NOT
%left ASSGNOP
%left '+' '-'
%left '*' '/'


%%

input 	: line
	;

line	: explist
	| explist println
	| println
	| /*empty*/
	;

println	: PRINTLN '(' rprint 	{}
	;

rprint	: STRING ',' rprint	{}
	| explist ',' rprint	{}
	| print			{;}
	;

print	: STRING ')' line	{}
	| explist ')' line	{}
	;  

explist : exp		{
				iterator->elem = $1;
				iterator->next = malloc (sizeof(AST_list));
				iterator = iterator->next;
			}

	| explist exp	{
				iterator->elem = $2;
				iterator->next = malloc (sizeof(AST_list));
				iterator = iterator->next;
				iterator->next = NULL;
			}
	;

exp	: NUMBER		{$$ = make_integer($1);}
	| FLOAT			{$$ = make_float($1);}
	| BOOLEAN		{$$ = make_bool($1);}
	| IDENTIFIER		{$$ = make_variable($1);}
	| IDENTIFIER ASSGNOP exp{$$ = make_assign($1, $3);}
	| exp '+' exp		{$$ = make_logical("+", $1, $3);}
	| exp '-' exp		{$$ = make_logical("-", $1, $3);}
	| exp '*' exp		{$$ = make_logical("*", $1, $3);}
	| exp '/' exp		{$$ = make_logical("/", $1, $3);}
	| exp EQUALS exp	{$$ = make_logical("==",$1,$3);}
	| exp DIFFER exp	{$$ = make_logical("!=",$1,$3);}
	| exp LT exp		{$$ = make_logical("<",$1,$3);}
	| exp GT exp		{$$ = make_logical(">",$1,$3);}
	| exp LET exp		{$$ = make_logical("<=",$1,$3);}
	| exp GET exp		{$$ = make_logical(">=",$1,$3);}
	| NOT BOOLEAN		{;}
	| '(' exp ')'		{$$ = $2;}
	;

%%

/*=========================================================================
MAIN
=========================================================================*/

//var declaration
AST_list *root;
AST_list *iterator;

Code_list *int_code;
Code_list *int_iterator;

int linenum = 0;


main(int argc, char *argv[]){

	root = malloc(sizeof(AST_list));
	iterator = root;

	int_code = malloc(sizeof(Code_list));
	int_iterator = int_code;

	initialize_var_list();

	extern FILE *yyin;
	++argv;
	--argc;
	yyin = fopen (argv[0], "r");

	yyparse();

	while(root->next != NULL){
		//convert to 3AC		
		printer(root->elem);
		printf("\n");
		convert_address(root->elem);
		root = root->next;
	}

	write_shit(int_code);

	printf("\n");
}
