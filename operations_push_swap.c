#include "push_swap.h"

int sa(t_list **lst)
{
    static int sa_count;
    t_list *temp;
    
    if (!lst || !*lst || !(*lst)->next)
        return (0);
    temp = (*lst)->next;
	(*lst)->next = temp->next;
    ps_lstadd_front(lst, temp);

    //sa_count = 0;
    sa_count++;
    write(1, "sa\n", 3);
    return(sa_count);
}

int sb(t_list **lst)
{
    static int sb_count;

    t_list  *first;
    t_list  *second;

    if (!lst || !*lst || !(*lst)->next)
        return (0);

    first = *lst;
    second = first->next;

    first->next = second->next;
    second->next = first;
    *lst = second;

    //sb_count = 0;
    sb_count++;
    write(1, "sa\n", 3);
    return (sb_count);
}

//ss
//pa
int pa(t_list **stack_a, t_list **stack_b)
{
    static int  pa_count;
    t_list *first_a;
    t_list *first_b;
    t_list *second_b;

    first_a = *stack_a; 
    first_b = *stack_b;
    second_b = (*stack_b)->next;
    ps_lstadd_front(stack_a, first_b);
    //ps_lstdelfirst(stack_b);
    *stack_b = second_b;

    write(1, "pa\n", 3);
    return (pa_count);
}
//pb

int pb(t_list **stack_b, t_list **stack_a)
{
    static int  pb_count;
    t_list *first_a;
    t_list *second_a;
    t_list *first_b;

    first_a = *stack_a;
    second_a = (*stack_a)->next;
    first_b = *stack_b;
    ps_lstadd_front(stack_b, first_a);
    //ps_lstdelfirst(stack_a);
    *stack_a = second_a;
    
    write(1, "pb\n", 3);
    return (pb_count);
}