#include "push_swap.h"
//rra
int rra(t_list **stack_a)
{
    static int  rra_count;
    t_list *last_a;
    t_list *com;

    if (!stack_a || !*stack_a)
        return (0);

    last_a = *stack_a;
    
    while (last_a->next)
    {
        com = last_a;
        last_a = last_a->next;
    }
    com->next = NULL;
    ps_lstadd_front(stack_a, last_a);
    //printf("penultimo = %i", com->value);
    //printf("last value = %i", last_a->value);
    
    write(1, "rra\n", 3);
    return (rra_count);
}
//rrb
int rrb(t_list **stack_b)
{
    static int  rrb_count;
    t_list *last_b;
    t_list *com;

    if (!stack_b || !*stack_b)
        return (0);

    last_b = *stack_b;
    
    while (last_b->next)
    {
        com = last_b;
        last_b = last_b->next;
    }
    com->next = NULL;
    ps_lstadd_front(stack_b, last_b);
    //printf("penultimo = %i", com->value);
    //printf("last value = %i", last_a->value);
    
    write(1, "rrb\n", 3);
    return (rrb_count);
}
//rrr