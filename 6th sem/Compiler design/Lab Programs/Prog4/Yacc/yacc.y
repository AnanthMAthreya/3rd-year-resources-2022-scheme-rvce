%{
    #include<stdio.h>
    #include<stdlib.h>
    int cnt=0;
%}
%token IF IDEN NUM
%%
S:I
;
I:IF A B    {cnt++;}
;
A:'('E')'
;
E:IDEN Z IDEN
|IDEN Z NUM
|IDEN U
|IDEN
;
Z:'='|'<'|'>'|'<''='|'>''='|'=''+'|'=''-'
;
U:'+''+'|'-''-'
;
B:B B
|'{'B'}'
|I
|E';'
|
;
%%
int main()
{
    printf("Enter the snippet:\n");
    yyparse();
    printf("Count of if is %d\n",cnt);
    return 0;
}
int yyerror()
{
    printf("Invalid\n");
    exit(0);
}