%{
    #include <stdio.h>
    #include <math.h>
    int yylex(void);
    void yyerror(const char *);
    
    #define YYSTYPE double
%}

%token NUM

%%

input:
  /* empty */
| input line
;

line:
  '\n'
| exp '\n'      { printf("%.10g\n", $1); }

exp:
  NUM           { $$ = $1; }
| exp exp '+'   { $$ = $1 + $2; }
| exp exp '-'   { $$ = $1 - $2; }
| exp exp '*'   { $$ = $1 * $2; }
| exp exp '/'   { $$ = $1 / $2; }
| exp exp '^'   { $$ = pow($1, $2); }
| exp 'n'       { $$ = -$1; }
;

%%

int yylex (void)
{
    int c;

    while ((c = getchar ()) == ' ' || c == '\t')
        continue;

    if (c == '.' || isdigit (c))
    {
        ungetc (c, stdin);
        scanf ("%lf", &yylval);
        return NUM;
    }

    if (c == EOF)
        return 0;

    return c;
}

void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main(void)
{
    return yyparse();
}

