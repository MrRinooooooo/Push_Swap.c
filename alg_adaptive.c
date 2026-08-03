#include "push_swap.h"

void	alg_selector(int *flags, int *int_arr, t_list **stack_a, t_list **stack_b, int size)
{
	char 		*strategy;
	float       disorder;
	t_count     count;

	init_counts(&count);
	disorder = compute_disorder(int_arr, size);
	if (flags[1] == 0 && flags[2] == 0 && flags[3] == 0)
    	flags[4] = 1;
	if (flags[4] == 1)
		strategy = adaptive_sort(disorder, flags);
	if (flags[1] == 1)
	{
		simple_sort(stack_a, stack_b, &count);
		strategy = "O(n^2)";
	}
	else if (flags[2] == 1)
	{
		medium_sort(stack_a, stack_b, size, &count);
		strategy = "O(n sqrt n)";
	}
	else if (flags[3] == 1)
	{
		complex_sort(stack_a, stack_b, size, &count);
		strategy = "O(n log n)";
	}
	if (flags[0] == 1)
		print_bench(count, disorder, flags, strategy);

	printf("\n");
	print_stack_rank(*stack_a);
	print_stack_rank(*stack_b);
}

char	*adaptive_sort(float disorder, int *flags)
{
	if (disorder < 0.2)
	{
		flags[1] = 1;
		return ("O(n^2)");
	}
	else if (disorder >= 0.2 && disorder < 0.5)
	{
		flags[2] = 1;
		return ("O(n sqrt n)");
	}
	else
	{
		flags[3] = 1;
		return ("O(n log n)");
	}
}