#include "push_swap.h"

void    sa(t_list **lst, t_count *count)
{
    t_list  *temp;
    
    if (!lst || !*lst || !(*lst)->next)
        return (0);
    temp = (*lst)->next;
	(*lst)->next = temp->next;
    ps_lstadd_front(lst, temp);
    count->sa++;
    write(1, "sa\n", 3);
}

void    sb(t_list **lst, t_count *count)
{
    t_list  *first;
    t_list  *second;

    if (!lst || !*lst || !(*lst)->next)
        return (0);
    first = *lst;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *lst = second;
    count->sb++;
    write(1, "sb\n", 3);
}

void    pa(t_list **stack_a, t_list **stack_b, t_count *count)
{
    t_list *first_a;
    t_list *first_b;
    t_list *second_b;

    first_a = *stack_a; 
    first_b = *stack_b;
    second_b = (*stack_b)->next;
    ps_lstadd_front(stack_a, first_b);
    *stack_b = second_b;
    count->pa++;
    write(1, "pa\n", 3);
}

void    pb(t_list **stack_b, t_list **stack_a, t_count *count)
{
    t_list *first_a;
    t_list *second_a;
    t_list *first_b;

    first_a = *stack_a;
    first_b = *stack_b;
    second_a = (*stack_a)->next;
    ps_lstadd_front(stack_b, first_a);
    *stack_a = second_a;
    count->pb++;
    write(1, "pb\n", 3);
}