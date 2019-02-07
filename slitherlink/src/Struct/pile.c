#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

stack_s *stack_create (void)
{
   return (NULL);
}

void stack_push (stack_s ** my_stack, void *data)
{
   if (my_stack != NULL)
   {
      stack_s *my_old_stack = *my_stack;
      stack_s *my_new_stack = NULL;

      my_new_stack = malloc (sizeof (*my_new_stack));
      if (my_new_stack != NULL)
      {
         my_new_stack->data = data;
         my_new_stack->next = NULL;
         my_new_stack->prev = my_old_stack;
         if (my_old_stack != NULL)
            my_old_stack->next = my_new_stack;
         *my_stack = my_new_stack;
      }
      else
      {
         fprintf (stderr, "Not enough space !\n");
         exit (EXIT_FAILURE);
      }
   }
   return;
}

void *stack_pop (stack_s ** my_stack)
{
   void *returned_data = NULL;

   if (my_stack != NULL && *my_stack != NULL)
   {
      stack_s *my_new_stack = *my_stack;
      stack_s *my_old_stack = my_new_stack->prev;

      if (my_old_stack != NULL)
         my_old_stack->next = NULL;
      returned_data = my_new_stack->data;
      free (my_new_stack);
      my_new_stack = NULL;
      *my_stack = my_old_stack;
   }
   return (returned_data);
}

void stack_delete (stack_s ** my_stack)
{
   if (my_stack != NULL && *my_stack != NULL)
   {
      while (*my_stack != NULL)
         stack_pop (my_stack);
   }
   return;
}
