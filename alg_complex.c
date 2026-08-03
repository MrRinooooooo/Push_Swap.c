#include "push_swap.h"

static void	scan_partition_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
	int remaining;

    remaining = range->size;
    range->pushed = 0;
    range->rotates = 0;
	while (remaining > 0 && *a)
	{
		if ((*a)->rank < range->pivot)
		{
			pb(b, a, count, 1); //meta bassa, spinge il num in B
			range->pushed++;
		}
		else
		{
			ra(a, count, 1); //meta alta, lo ruoto in fondo ad A
			range->rotates++;
		}
		remaining--;
	}
}

static void undo_partition_a(t_list **a, t_count *count, int rotates)
{
    while (rotates > 0)
    {
        rra(a, count,1); //sposta l'ultimo elemento in testa
        rotates--;
    }
}

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

static void	scan_partition_b(t_list **a, t_list **b, t_range *range, t_count *count)
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

static void	undo_partition_b(t_list **b, t_count *count, int rotates)
{
	while (rotates > 0)
	{
		rrb(b, count, 1);
		rotates--;
	}
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
	next.size = range->size - pushed;
	next.min = pivot;
	next.max = range->max;
	sort_a(a, b, &next, count);
    damn_norm(range, &next, pushed, pivot);
    /*
	next.size = pushed;
	next.min = range->min;
	next.max = pivot - 1;
    */
	sort_b(a, b, &next, count);
}

void	sort_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
	t_range	part;
	t_range	next;
	int		pivot;
	int		pushed;
	int		remaining;

	if (range->size < 1)
		return ;
	if (is_range_sorted_b(*b, range->size))
	{
		remaining = range->size;
		while (remaining > 0)
		{
			pa(a, b, count, 1);
			remaining--;
		}
		return ;
	}
	if (range->size == 2)
	{
		if ((*b)->rank < (*b)->next->rank)
			sb(b, count, 1);
		pa(a, b, count, 1);
		pa(a, b, count, 1);
		return ;
	}
	pivot = range->min + range->size / 2;
	part.size = range->size;
	part.pivot = pivot;
	pushed = partition_b(a, b, &part, count);
	next.size = pushed;
	next.min = pivot + 1;
	next.max = range->max;
	sort_a(a, b, &next, count);
    damn_norm(range, &next, pushed, pivot);
	/*
    next.size = range->size - pushed;
	next.min = range->min;
	next.max = pivot;
    */
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

void damn_norm(t_range *range, t_range *next, int pushed, int pivot)
{
    next->size = range->size - pushed;
	next->min = range->min;
	next->max = pivot;
}