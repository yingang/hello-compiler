#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// "constructors"
struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Minus_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_MINUS;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Times_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_TIMES;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Devide_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_DEVIDE;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}

/// instruction list

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// "printer"
void List_reverse_print (struct List_t *list)
{
  if (list->next != 0)
    List_reverse_print(list->next);
  
  switch (list->instr->kind) {
  case STACK_ADD: {
    printf("ADD\n");
    break;
  }
  case STACK_MINUS: {
    printf("MINUS\n");
    break;
  }
  case STACK_TIMES: {
    printf("TIMES\n");
    break;
  }
  case STACK_DEVIDE: {
    printf("DEVIDE\n");
    break;
  }
  case STACK_PUSH: {
    struct Stack_Push *sp = (struct Stack_Push *)list->instr;
    printf("PUSH %d\n", sp->i);
    break;
  }
  default:
    break;
  }
}

//////////////////////////////////////////////////
// a compiler from AST to Stack

struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->n));
    break;
  }
  case EXP_ADD:{
    struct Exp_Add *sp = (struct Exp_Add *)exp;
    compile (sp->left);
    compile (sp->right);
    emit (Stack_Add_new ());
    break;
  }
  case EXP_MINUS:{
    struct Exp_Minus *sp = (struct Exp_Minus *)exp;
    compile (sp->left);
    compile (sp->right);
    emit (Stack_Minus_new ());
    break;
  }
  case EXP_TIMES:{
    struct Exp_Times *sp = (struct Exp_Times *)exp;
    compile (sp->left);
    compile (sp->right);
    emit (Stack_Times_new ());
    break;
  }
  case EXP_DEVIDE:{
    struct Exp_Devide *sp = (struct Exp_Devide *)exp;
    compile (sp->left);
    compile (sp->right);
    emit (Stack_Devide_new ());
    break;
  }
  default:
    break;
  }
}

