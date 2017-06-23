/*=========================================================================
C-libraries and Token definitions
=========================================================================*/
%{
#include <string.h> /* for strdup */
#include <stdlib.h> /* for atoi */
#include "trabalho.tab.h" /* for token definitions and yylval */

extern int linenum;
%}

DIGIT [0-9]
ID [a-z][a-z0-9]*

%%

"=" 	{ return(ASSGNOP); }
"==" 	{ return(EQUALS); }
"!="	{ return(DIFFER);}
"<" 	{ return(LT); }
">" 	{ return(GT); }
"<=" 	{ return(LET); }
">=" 	{ return(GET); }
"!" 	{ return(NOT); }

{DIGIT}+ {
	yylval.num = (int ) atoi(yytext);
	return(NUMBER); 
}
{DIGIT}+\.{DIGIT}+ {
	yylval.flo = (float ) atof(yytext);
	return(FLOAT);
}

true	{ 
	yylval.boo = yytext;
	return(BOOLEAN); 
}
false	{ 
	yylval.boo = yytext;
	return(BOOLEAN); 
}
integer { return(INTEGER); }
do 	{ return(DO); }
else 	{ return(ELSE); }
if 	{ return(IF); }
end 	{ return(END); }
let 	{ return(LET); }
in	{ return(IN); }
then 	{ return(THEN); }
while 	{ return(WHILE); }
println { return(PRINTLN); }
{ID} 	{ 
	yylval.id = (char *) strdup(yytext);
	return(IDENTIFIER); 
}

L?\"(\\.|[^\\"])*\"	{ 
	printf("string: %s\n", yytext);
	return (STRING);
}

[ \t]+  ;
\n	{ linenum++; }
. 	{ return(yytext[0]);}
%%

int yywrap(void){
	return 1;
}
