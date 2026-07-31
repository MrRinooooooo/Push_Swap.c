#include "push_swap.h"

void    rra(t_list **stack_a, t_count *count)
{
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
    count->rra++;
    write(1, "rra\n", 4);
}

void    rrb(t_list **stack_b, t_count *count)
{
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
    count->rrb++;    
    write(1, "rrb\n", 4);
}