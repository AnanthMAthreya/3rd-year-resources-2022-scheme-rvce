%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin; // optional


typedef char *string;

struct {
	string res, op1, op2;
	char op;
} code[100];
int idx = -1;

string addToTable(string, string, char);
void threeAddressCode();
void quadruples();
%}

%union {
	char *exp;
}

%token <exp> IDEN NUM
%type <exp> EXP

%left '+' '-'
%left '*' '/'

%%

STMTS	: STMTS STMT
	|
	;

STMT	: EXP '\n'
	;

EXP	: EXP '+' EXP { $$ = addToTable($1, $3, '+'); }
	| EXP '-' EXP { $$ = addToTable($1, $3, '-'); }
	| EXP '*' EXP { $$ = addToTable($1, $3, '*'); }
	| EXP '/' EXP { $$ = addToTable($1, $3, '/'); }
	| '(' EXP ')' { $$ = $2; }
	| IDEN '=' EXP { $$ = addToTable($1, $3, '='); }
	| IDEN { $$ = $1; }
	| NUM { $$ = $1; }
	;

%%

int yyerror() {
	printf("Error");
	exit(0);
}

int main() {
	// yyin = fopen("6.txt", "r"); 
	// Only if input is given from text file
	yyparse();

	printf("\nThree address code:\n");
	threeAddressCode();

	printf("\nQuadruples:\n");
	quadruples();
}


string addToTable(string op1, string op2, char op) {
	if(op == '=') {
		code[idx].res = op1;
		return op1;
	}

	idx++;
	string res = malloc(3);
	sprintf(res, "@%c", idx + 'A');
	code[idx].op1 = op1;
	code[idx].op2 = op2;
	code[idx].op = op;
	code[idx].res = res;
	return res;
}

void threeAddressCode() {
	for(int i = 0; i <= idx; i++) {
		printf("%s = %s %c %s\n", code[i].res, code[i].op1, code[i].op, code[i].op2);
	}
}


void quadruples() {
	for(int i = 0; i <= idx; i++) {
		printf("%d:\t%s\t%s\t%s\t%c\n", i, code[i].res, code[i].op1, code[i].op2, code[i].op);
	}
}
