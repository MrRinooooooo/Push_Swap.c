#include "push_swap.h"

void ra(t_list **stack_a, t_count *count)
{
    t_list *first_a;
    t_list *second_a;
    t_list *node;

    if (!stack_a || !*stack_a)
        return (0);
    first_a = *stack_a;
    second_a = (*stack_a)->next;
    node = *stack_a;
    while (node->next)
        node = node->next;
    node->next = first_a;
    first_a->next = NULL;
    *stack_a = second_a;
    count->ra++;
    write(1, "ra\n", 3);
}

void rb(t_list **stack_b, t_count *count)
{
    t_list *first_b;
    t_list *second_b;
    t_list *node;

    if (!stack_b || !*stack_b)
        return (0);
    first_b = *stack_b;
    second_b = (*stack_b)->next;   
    node = *stack_b;
    while (node->next)
        node = node->next;
    node->next = first_b;
    first_b->next = NULL;
    *stack_b = second_b;
    count->rb++;
    write(1, "rb\n", 3);
}