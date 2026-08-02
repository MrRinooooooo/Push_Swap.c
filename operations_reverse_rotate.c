#include "push_swap.h"

void    rra(t_list **stack_a, t_count *count, int print)
{
    t_list *last_a;
    t_list *com;

    if (!stack_a || !*stack_a)
        return ;
    last_a = *stack_a;
    while (last_a->next)
    {
        com = last_a;
        last_a = last_a->next;
    }
    com->next = NULL;
    ps_lstadd_front(stack_a, last_a);
    count->rra++;
    if (print == 1)
        write(1, "rra\n", 4);
}

void    rrb(t_list **stack_b, t_count *count, int print)
{
    t_list *last_b;
    t_list *com;

    if (!stack_b || !*stack_b)
        return ;
    last_b = *stack_b;
    while (last_b->next)
    {
        com = last_b;
        last_b = last_b->next;
    }
    com->next = NULL;
    ps_lstadd_front(stack_b, last_b);
    count->rrb++;
    if (print == 1)count->rrb++;
        write(1, "rrb\n", 4);
}

void    rrr(t_list **stack_a, t_list **stack_b, t_count *count, int print)
{
    rra(stack_a, count, 0);
    rrb(stack_b, count, 0);
    count->rrb--;
    count->rrb--;
    count->rrr++;
    if (print == 1)
        write(1, "rrr\n", 4);
}