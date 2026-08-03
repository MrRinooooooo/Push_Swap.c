#include "push_swap.h"

int	is_range_sorted_b(t_list *b, int size)
{
	if (!b || size <= 1)
		return (1);
	while (size > 1 && b && b->next)
	{
		if (b->rank < b->next->rank)
			return (0);
		b = b->next;
		size--;
	}
	return (1);
}

int	is_range_sorted_a(t_list *a, int size)
{
	if (!a || size <= 1)
		return (1);
	while (size > 1 && a && a->next)
	{
		if (a->rank > a->next->rank)
			return (0);
		a = a->next;
		size--;
	}
	return (1);
}

void	damn_norm(t_range *next, int size, int min, int max)
{
	next->size = size;
	next->min = min;
	next->max = max;
}

void	damn_norm2(t_list **a, t_list **b, t_count *count)
{
	if ((*b)->rank < (*b)->next->rank)
		sb(b, count, 1);
	pa(a, b, count, 1);
	pa(a, b, count, 1);
}

void	damn_norm3(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int	remaining;

	remaining = range->size;
	while (remaining-- > 0)
		pa(a, b, count, 1);
}
