#include "push_swap.h"

void ra(t_list **stack_a, t_count *count, int print)
{
    t_list *first_a;
    t_list *second_a;
    t_list *node;

    if (!stack_a || !*stack_a)
        return ;
    first_a = *stack_a;
    second_a = (*stack_a)->next;
    node = *stack_a;
    while (node->next)
        node = node->next;
    node->next = first_a;
    first_a->next = NULL;
    *stack_a = second_a;
    count->ra++;
    if (print == 1)
        write(1, "ra\n", 3);
}

void rb(t_list **stack_b, t_count *count, int print)
{
    t_list *first_b;
    t_list *second_b;
    t_list *node;

    if (!stack_b || !*stack_b)
        return ;
    first_b = *stack_b;
    second_b = (*stack_b)->next;   
    node = *stack_b;
    while (node->next)
        node = node->next;
    node->next = first_b;
    first_b->next = NULL;
    *stack_b = second_b;
    count->rb++;
    if (print == 1)
        write(1, "rb\n", 3);
}

void rr(t_list **stack_a, t_list **stack_b, t_count *count, int print)
{
    ra(stack_a, count, 0);
    rb(stack_b, count, 0);
    count->ra--;
    count->rb--;
    count->rr++;
    if (print == 1)
        write(1, "rr\n", 3);
}