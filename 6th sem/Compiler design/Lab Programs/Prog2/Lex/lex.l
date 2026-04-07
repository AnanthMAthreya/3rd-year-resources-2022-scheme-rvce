%{
#include <stdio.h>
int posint = 0, negint = 0, posfrac = 0, negfrac = 0;
%}

num [0-9]+

posint \+?{num}
negint -{num}

posnum \+?{num}\.{num}?|\+?\.{num}
negnum -{num}\.{num}?|-\.{num}

%%

{posint} posint++;

{negint} negint++;

{posnum} posfrac++;

{negnum} negfrac++;

{posnum}\/{posnum} |
{negnum}\/{negnum} posfrac++;

{posnum}\/{negnum} |
{negnum}\/{posnum} negfrac++;

[ \t] ;

[\n] return 0;

. ECHO;

%%

int yywrap(){}

int main() {
	yylex();
	printf("Positive integers: %d\n", posint);
	printf("Negative integers: %d\n", negint);
	printf("Positive fractions: %d\n", posfrac);
	printf("Negative fractions: %d\n", negfrac);
}
