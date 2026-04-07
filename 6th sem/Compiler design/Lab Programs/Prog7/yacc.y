%{
    #include<stdio.h>
    #include<stdlib.h>
%}

%token TYPE IDEN NUM RET
 
%%
S: FUN  {printf("Accepted\n");exit(0);}
;
FUN:    TYPE IDEN '(' PARAM ')' '{' BODY '}'
;
PARAM: PARAM ',' PARAM
|TYPE IDEN
|
;
BODY: BODY BODY
| PARAM ';'
| E ';'
| RET E ';'
|
;
E: IDEN '=' E
| E '+' E
| E '-' E
| E '*' E
| E '/' E
| IDEN
| NUM
;
%%
int main()
{
    printf("enter input: ");
    yyparse();
    printf("successfull\n");
    return 0;
}
int yyerror()
{
    printf("ERROR\n");
    exit(0);
}