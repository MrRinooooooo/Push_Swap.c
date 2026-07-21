#include "push_swap.h"
//ra
int ra(t_list **stack_a)
{
    static int  ra_count;
    t_list *first_a;
    t_list *second_a;
    t_list *node;

    if (!stack_a || !*stack_a)
        return (0);

    first_a = *stack_a;
    second_a = (*stack_a)->next;
    
    while (node->next)
        node = node->next;

    node->next = first_a;
    first_a->next = NULL;
    *stack_a = second_a;
    
    write(1, "ra\n", 3);
    return (ra_count);
}
//rb
int rb(t_list **stack_b)
{
    static int  rb_count;
    t_list *first_b;
    t_list *second_b;
    t_list *node;

    if (!stack_b || !*stack_b)
        return (0);
    first_b = *stack_b;
    second_b = (*stack_b)->next;
    
    while (node->next)
        node = node->next;

    node->next = first_b;
    first_b->next = NULL;
    *stack_b = second_b;
    
    write(1, "rb\n", 3);
    return (rb_count);
}
//rr