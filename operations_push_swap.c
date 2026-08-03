#include "push_swap.h"

void	sa(t_list **lst, t_count *count, int print)
{
	t_list	*temp;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	temp = (*lst)->next;
	(*lst)->next = temp->next;
	ps_lstadd_front(lst, temp);
	count->sa++;
	if (print == 1)
		write(1, "sa\n", 3);
}

void	sb(t_list **lst, t_count *count, int print)
{
	t_list	*first;
	t_list	*second;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	first = *lst;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*lst = second;
	count->sb++;
	if (print == 1)
		write(1, "sb\n", 3);
}

void	ss(t_list **a, t_list **b, t_count *count, int print)
{
	sa(a, count, 0);
	sb(b, count, 0);
	count->sa--;
	count->sb--;
	count->ss++;
	if (print == 1)
		write(1, "ss\n", 3);
}

void	pa(t_list **stack_a, t_list **stack_b, t_count *count, int print)
{
	t_list	*first_b;
	t_list	*second_b;

	if (!stack_b || !*stack_b)
		return ;
	first_b = *stack_b;
	second_b = (*stack_b)->next;
	ps_lstadd_front(stack_a, first_b);
	*stack_b = second_b;
	count->pa++;
	if (print == 1)
		write(1, "pa\n", 3);
}

void	pb(t_list **stack_b, t_list **stack_a, t_count *count, int print)
{
	t_list	*first_a;
	t_list	*second_a;

	if (!stack_a || !*stack_a)
		return ;
	first_a = *stack_a;
	second_a = (*stack_a)->next;
	ps_lstadd_front(stack_b, first_a);
	*stack_a = second_a;
	count->pb++;
	if (print == 1)
		write(1, "pb\n", 3);
}
