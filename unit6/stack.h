#ifndef STACK_H
#define STACK_H

#include "ast.h"

//////////////////////////////////////////////
// Data structures for the Stack language.

enum Stack_Kind_t {
  STACK_ADD,
  STACK_MINUS,
  STACK_TIMES,
  STACK_DEVIDE,
  STACK_PUSH};

struct Stack_t
{
  enum Stack_Kind_t kind;
};

struct Stack_Add
{
  enum Stack_Kind_t kind;
};

struct Stack_Minus
{
  enum Stack_Kind_t kind;
};

struct Stack_Times
{
  enum Stack_Kind_t kind;
};

struct Stack_Devide
{
  enum Stack_Kind_t kind;
};

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

// "constructors"
struct Stack_t *Stack_Add_new ();

struct Stack_t *Stack_Minus_new ();

struct Stack_t *Stack_Times_new ();

struct Stack_t *Stack_Devide_new ();

struct Stack_t *Stack_Push_new (int i);

/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next);

// "printer"
void List_reverse_print (struct List_t *list);

//////////////////////////////////////////////////
// a compiler from AST to Stack

void emit (struct Stack_t *instr);

void compile (struct Exp_t *exp);

#endif
