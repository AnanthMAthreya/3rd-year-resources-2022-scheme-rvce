%{
#include <string.h>

#include "y.tab.h"
%}


%%

[a-zA-Z_][a-zA-Z_0-9]* {
	yylval.exp = strdup(yytext);
	return IDEN;
}

[0-9]+ {
	yylval.exp = strdup(yytext);
	return NUM;
}

[-+*/] return yytext[0];

[()=] return yytext[0];

[\n]+ return '\n';

[ \t]+ ;

. ;

%%

