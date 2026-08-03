#include "push_swap.h"

char	*simple_sort(t_list **a, t_list **b, t_count *count)
{
	if (is_sorted(*a))
		return ("O(n^2)");
	while (*a != NULL)
	{
		move_to_top(a, count);
		pb(b, a, count, 1);
	}
	while (*b != NULL)
		pa(a, b, count, 1);
	return ("O(n^2)");
}

void	move_to_top(t_list **a, t_count *count)
{
	int	min_pos;
	int	size;
	int	moves;

	min_pos = find_min_index(*a);
	size = stack_size(*a);
	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			ra(a, count, 1);
			min_pos--;
		}
	}
	else
	{
		moves = size - min_pos;
		while (moves > 0)
		{
			rra(a, count, 1);
			moves--;
		}
	}
}

int	find_min_index(t_list *stack)
{
	int		min;
	int		min_pos;
	int		pos;
	t_list	*current;

	min = stack->value;
	min_pos = 0;
	pos = 0;
	current = stack;
	while (current->next != NULL)
	{
		current = current->next;
		pos++;
		if (current->value < min)
		{
			min = current->value;
			min_pos = pos;
		}
	}
	return (min_pos);
}
