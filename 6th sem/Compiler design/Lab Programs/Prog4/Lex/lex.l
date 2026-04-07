%{
    #include<stdio.h>
    int id=0,key=0,op=0;
%}

%%
"int"|"char"|"float"|"double"|"if"|"else"|"for"|"while"|"exit"|"return" {printf("Keyword\n");key++;}
[a-zA-Z_][a-zA-Z0-9_]*  {printf("Identifier\n");id++;}
[\+\-\*\/\%\^\&\|\!\=]  {printf("Operator\n");op++;}
[^\n]*  {printf("Invalid\n");}
%%


int main()
{
    printf("Enter:\n");
    yylex();
    printf("Identifiers: %d\nKeywords: %d\nOperators: %d\n",id,key,op);
    return 0;
}
int yywrap()
{
    return 1;
}