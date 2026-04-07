%{
#include <stdio.h>
#include <stdlib.h>

//extern FILE *yyin;

typedef char *string;

struct {
	string res, op1, op2;
	char op;
} code[100];
int idx = -1;

string addToTable(string, string, char);
void targetCode();
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

int yyerror(const char *s) {
	printf("Error %s", s);
	exit(0);
}

int main() {
	//yyin = fopen("8.txt", "r");
	yyparse();

	printf("\nTarget code:\n");
	targetCode();
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

void targetCode() {
	for(int i = 0; i <= idx; i++) {
		string instr;
		switch(code[i].op) {
		case '+': instr = "ADD"; break;
		case '-': instr = "SUB"; break;
		case '*': instr = "MUL"; break;
		case '/': instr = "DIV"; break;
		}

		printf("LOAD\t R1, %s\n", code[i].op1);
		printf("LOAD\t R2, %s\n", code[i].op2);
		printf("%s\t R3, R1, R2\n", instr);
		printf("STORE\t %s, R3\n", code[i].res);
	}
}
