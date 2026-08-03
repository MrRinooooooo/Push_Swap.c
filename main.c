#include "push_swap.h"

int	main(int argc, char *argv[])
{
	static int	flags[5];
	int			*int_arr;
	t_list		*stack_a;
	t_list		*stack_b;
	int			size;

	int_arr = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (0);
	flags_set_zero(flags);
	flags_parser(flags, argc, argv);
	int_arr = int_arr_parser(argc, argv, flags_num(flags, int_arr));
	size = argc - flags_num(flags, int_arr) - 1;
	stack_a = list_arg_parser(int_arr, size);
	alg_selector(flags, int_arr, &stack_a, &stack_b, size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	free(int_arr);
	return (0);
}
