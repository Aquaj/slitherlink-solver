#ifndef ___pile_h___
#define ___pile_h___


struct stack
{
   struct stack *prev;
   struct stack *next;
   void *data;
};

typedef struct stack stack_s;

stack_s *stack_create (void);

void stack_push (stack_s **, void *);

void *stack_pop (stack_s **);

void stack_delete (stack_s **);

#endif
