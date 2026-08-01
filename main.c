#include "push_swap.h"

int main(int argc, char *argv[])
{
    static int  flags[5];
    int         *int_arr;
    t_list      *stack_a;
    t_list      *stack_b;
    int         size;

    stack_b = NULL;
    if (argc == 1)
        return (0);
    flags_set_zero(flags);
    flags_parser(flags, argc, argv);
    int_arr = int_arr_parser(argc, argv, flags_num(flags));
    size = argc - flags_num(flags) - 1;
    stack_a = list_arg_parser(int_arr, size);
	alg_selector(flags, int_arr, &stack_a, &stack_b, size);
    //init_counts(&count);
    //simple_sort(&stack_a, &stack_b, &count);
    //exec_medium(&stack_a, &stack_b, size, &count);
    //print_bench(count, disorder, flags, "O(n^2)");

    //RICORDARSI DI SOSTITUIRE TUTTI I PRINTF!!!!!!!!!!!!!
    //RICORDASI FREE(INT_ARRAY) E FREE(stack)
    return(0);
}