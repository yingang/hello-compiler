#include <stdio.h>

#include "ast.h"
#include "stack.h"

extern Exp_t tree;
extern struct List_t *all;

void yyparse ();

int main (int argc, char **argv)
{
  yyparse();

  printf ("\n");
  Exp_print (tree);
  
  // compile this tree to Stack machine instructions
  printf ("\n");
  compile (tree);

  // print out the generated Stack instructions:
  printf("\n");
  List_reverse_print (all);
 
  return 0;
}
