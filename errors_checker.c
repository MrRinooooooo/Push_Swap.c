#include "push_swap.h"

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	integer_error_checker(int sign, int result, int digit)
{
	if (sign == 1)
	{
		if (result > (INT_MAX - digit) / 10)
			print_error();
	}
	else
	{
		if ((unsigned int)result > ((unsigned int)INT_MAX + 1 - digit) / 10)
			print_error();
	}
}

void	print_error_free_stack(t_list **stack_a, t_list **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	print_error();
}
