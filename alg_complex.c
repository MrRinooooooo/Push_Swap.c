#include "push_swap.h"

int partition_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int total_stack_a;
	int remaining;

	total_stack_a = stack_size(*a);//misura tutti gli elementi di A
	scan_partition_a(a, b, range, count);//scansione e smistamento
	remaining = range->size - range->pushed - range->rotates;
	if (total_stack_a > remaining)
		undo_partition_a(a, count, range->rotates);
	return (range->pushed);
}

int	partition_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int	total_stack;
	int	remaining;

	total_stack = stack_size(*b);
	scan_partition_b(a, b, range, count);
	remaining = range->size - range->pushed - range->rotates;
	if (total_stack > remaining)
		undo_partition_b(b, count, range->rotates);
	return (range->pushed);
}

void	sort_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
	t_range	part;
	t_range	next;
	int		pivot;
	int		pushed;

	if (range->size < 1 || is_range_sorted_a(*a, range->size))
		return ;
	if (range->size == 2)
	{
		if ((*a)->rank > (*a)->next->rank)
			sa(a, count, 1);
		return ;
	}
	pivot = range->min + range->size / 2;
	part.size = range->size;
	part.pivot = pivot;
	pushed = partition_a(a, b, &part, count);
	if (pushed == 0 || pushed == range->size)
		return ;
	damn_norm(&next, range->size - pushed, pivot, range->max);
	sort_a(a, b, &next, count);
	damn_norm(&next, pushed, range->min, pivot - 1);
	sort_b(a, b, &next, count);
}

void	sort_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
	t_range	part;
	t_range	next;
	int		pivot;
	int		pushed;

	if (range->size < 1)
		return ;
	if (is_range_sorted_b(*b, range->size))
	{
        damn_norm3(a, b, range, count);
		return ;
	}
	if (range->size == 2)
	{
        damn_norm2(a, b, count);
		return ;
	}
	pivot = range->min + range->size / 2;
	part.size = range->size;
	part.pivot = pivot;
	pushed = partition_b(a, b, &part, count);
	damn_norm(&next, pushed, pivot + 1, range->max);
	sort_a(a, b, &next, count);
	damn_norm(&next, range->size - pushed, range->min, pivot);
	sort_b(a, b, &next, count);
}

void	complex_sort(t_list **a, t_list **b, int size, t_count *count)
{
	t_range	range;

	if (size <= 1)
		return ;
	range.size = size;
	range.min = 0;
	range.max = size - 1;
	range.pivot = 0;
	sort_a(a, b, &range, count);
}
