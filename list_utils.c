#include "push_swap.h"

t_list	*ps_lstnew(int value)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ps_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ps_lstdelfirst(t_list **lst)
{
	t_list *first;

	if (!lst || !*lst)
		return ;
	first = *lst;
	*lst = (*lst)->next;
	free(first);
}

// FOR DEBUG
void	print_stack(t_list *lst)
{
	while (lst)
	{
		printf("%d\n", lst->value);
		lst = lst->next;
	}
}