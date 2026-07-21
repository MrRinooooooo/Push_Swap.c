#include "push_swap.h"

int sa(t_list **lst)
{
    static int sa_count;
    t_list *temp;
    
    if (!lst || !*lst || !(*lst)->next)
        return (0);
    temp = (*lst)->next;
	(*lst)->next = temp->next;
    ft_lstadd_front(lst, temp);

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
//int pa(t_list **stack_a, t_list **stack_b)

//pb