%{

#include <string.h>

int num_lines = 1, num_chars = 1;

%}

DIGIT    [0-9]
ID       [_A-Za-z][A-Za-z0-9]*

%%

{DIGIT}+	{
				printf( "NUM: %s (%d:%d)\n", yytext, num_lines, num_chars );
				num_chars += strlen(yytext);
			}

if			{
				printf( "IF: %s (%d:%d)\n", yytext, num_lines, num_chars );
				num_chars += 2;
			}

{ID}		{
				printf( "ID: %s (%d:%d)\n", yytext, num_lines, num_chars );
				num_chars += strlen(yytext);
			}

\n			++num_lines; num_chars=1;

[ ]			++num_chars;

.			{
				printf( "Unrecognized character: %s\n", yytext );
				++num_chars;
			}
%%

int main( int argc, char **argv )
{
	++argv, --argc;
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;

	yylex();
}

