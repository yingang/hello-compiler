%{
    #include <stdio.h>

    int yylex(void);
    void yyerror(const char *);
    
%}

%token NUM
%left '-' '+'
%left '*' '/'
%right '^'

%%

input:
  /* empty */
| input line
;

line:
  '\n'
| exp '\n'      { printf("%d\n", $1); }

exp:
  NUM           { $$ = $1; }
| exp '+' exp   { $$ = $1 + $3; }
| exp '-' exp   { $$ = $1 - $3; }
| exp '*' exp   { $$ = $1 * $3; }
| exp '/' exp   { $$ = $1 / $3; }
| '(' exp ')'   { $$ = $2; }
;

%%

int yylex (void)
{
    int c;

    while ((c = getchar ()) == ' ' || c == '\t')
        continue;

    if (isdigit (c))
    {
        ungetc (c, stdin);
        scanf ("%d", &yylval);
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

