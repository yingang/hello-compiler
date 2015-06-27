#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
  do{\
  printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
}while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error R2: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  switch (exp->kind)
  {
    case EXP_INT: {
      Exp_Int p = (Exp_Int)exp;
      return TYPE_INT;
    }
    case EXP_TRUE: {
      Exp_True p = (Exp_True)exp;
      return TYPE_BOOL;
    }
    case EXP_FALSE: {
      Exp_False p = (Exp_False)exp;
      return TYPE_BOOL;
    }
    case EXP_ID: {
      Exp_Id p = (Exp_Id)exp;
      Type_t type = Table_lookup(p->id);
  	  if (type == -1) {
  	    fprintf (stderr, "Error R1: the id "
	        "\"%s\" has not been declared\n", p->id);
	      exit(0);
  	  }
  	  return type;
    }
    case EXP_ADD: {
      Exp_Add p = (Exp_Add)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_INT) {
        fprintf (stderr, "Error R6: the left of '+' is not INT (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_INT) {
        fprintf (stderr, "Error R6: the right of '+' is not INT (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_INT;
    }
    case EXP_SUB: {
      Exp_Sub p = (Exp_Sub)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_INT) {
        fprintf (stderr, "Error R6: the left of '-' is not INT (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_INT) {
        fprintf (stderr, "Error R6: the right of '-' is not INT (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_INT;
    }
    case EXP_TIMES: {
      Exp_Times p = (Exp_Times)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_INT) {
        fprintf (stderr, "Error R6: the left of '*' is not INT (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_INT) {
        fprintf (stderr, "Error R6: the right of '*' is not INT (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_INT;
    }
    case EXP_DIVIDE: {
      Exp_Divide p = (Exp_Divide)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_INT) {
        fprintf (stderr, "Error R6: the left of '/' is not INT (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_INT) {
        fprintf (stderr, "Error R6: the right of '/' is not INT (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_INT;
    }
    case EXP_AND: {
      Exp_And p = (Exp_And)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_BOOL) {
        fprintf (stderr, "Error R7: the left of '&&' is not BOOL (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_BOOL) {
        fprintf (stderr, "Error R7: the right of '&&' is not BOOL (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_BOOL;
    }
    case EXP_OR: {
      Exp_Or p = (Exp_Or)exp;
      Type_t type_left = check_exp(p->left);
      if (type_left != TYPE_BOOL) {
        fprintf (stderr, "Error R7: the left of '||' is not BOOL (");
        Exp_print (p->left);
        printf (")\n");
        exit(0);
      }
      Type_t type_right = check_exp(p->right);
      if (type_right != TYPE_BOOL) {
        fprintf (stderr, "Error R7: the right of '||' is not BOOL (");
        Exp_print (p->right);
        printf (")\n");
        exit(0);
      }
      return TYPE_BOOL;
    }
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  switch (stm->kind)
  {
  	case STM_ASSIGN: {
  	  Stm_Assign p = (Stm_Assign)stm;

  	  Type_t type_left = Table_lookup(p->id);
  	  printf("%d", type_left);
  	  
  	  if (type_left == -1) {
  	    fprintf (stderr, "Error R1: the id "
	      "\"%s\" has not been declared\n", p->id);
	    exit(0);
  	  }
  	  
  	  Type_t type_right = check_exp(p->exp);

  	  if (type_left != type_right) {
  	    fprintf (stderr, "Error R3: the id "
	      "\"%s\" has different type with ", p->id);
	    Exp_print (p->exp);
	    printf ("\n");
	    exit(0);
  	  }
  	  break;
  	}
  	case STM_PRINTI: {
  	  Stm_Printi p = (Stm_Printi)stm;
  	  
  	  Type_t type = check_exp(p->exp);
  	  
  	  if (type != TYPE_INT) {
  	    fprintf (stderr, "Error R4: the input to printi is not INT, ");
        Exp_print (p->exp);
        printf("\n");
        exit(0);
  	  }
  	  break;
  	}
  	case STM_PRINTB: {
  	  Stm_Printb p = (Stm_Printb)stm;
  	  
  	  Type_t type = check_exp(p->exp);
  	  
  	  if (type != TYPE_BOOL) {
  	    fprintf (stderr, "Error R5: the input to printb is not BOOL, ");
        Exp_print (p->exp);
        printf("\n");
        exit(0);
  	  }
  	  break;
  	}
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
