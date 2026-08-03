#include "push_swap.h"

void	scan_partition_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int	remaining;

	remaining = range->size;
	range->pushed = 0;
	range->rotates = 0;
	while (remaining > 0 && *a)
	{
		if ((*a)->rank < range->pivot)
		{
			pb(b, a, count, 1);
			range->pushed++;
		}
		else
		{
			ra(a, count, 1);
			range->rotates++;
		}
		remaining--;
	}
}

void	undo_partition_a(t_list **a, t_count *count, int rotates)
{
	while (rotates > 0)
	{
		rra(a, count, 1);
		rotates--;
	}
}

void	scan_partition_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int	remaining;

	remaining = range->size;
	range->pushed = 0;
	range->rotates = 0;
	while (remaining > 0 && *b)
	{
		if ((*b)->rank > range->pivot)
		{
			pa(a, b, count, 1);
			range->pushed++;
		}
		else
		{
			rb(b, count, 1);
			range->rotates++;
		}
		remaining--;
	}
}

void	undo_partition_b(t_list **b, t_count *count, int rotates)
{
	while (rotates > 0)
	{
		rrb(b, count, 1);
		rotates--;
	}
}
