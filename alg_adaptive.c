#include "push_swap.h"

void	alg_selector(int *flags, int *arr, t_list **stack_a, t_list **stack_b)
{
	char		*strategy;
	float		disorder;
	t_count		count;
	int			size;

	size = stack_size(*stack_a);
	init_counts(&count);
	disorder = compute_disorder(arr, size);
	if (flags[1] == 0 && flags[2] == 0 && flags[3] == 0)
		flags[4] = 1;
	if (flags[4] == 1)
		strategy = adaptive_sort(disorder, flags, size);
	if (flags[1] == 1)
		strategy = simple_sort(stack_a, stack_b, &count);
	else if (flags[2] == 1)
		strategy = medium_sort(stack_a, stack_b, size, &count);
	else if (flags[3] == 1)
	{
		complex_sort(stack_a, stack_b, size, &count);
		strategy = "O(n log n)";
	}
	if (flags[0] == 1)
		print_bench(count, disorder, flags, strategy);
}

char	*adaptive_sort(float disorder, int *flags, int size)
{
	if (disorder < 0.2 && size < 100)
	{
		flags[1] = 1;
		return ("O(n^2)");
	}
	else if (size > 250)
	{
		flags[3] = 1;
		return ("O(n log n)");
	}
	else
	{
		flags[2] = 1;
		return ("O(n sqrt n)");
	}
}
