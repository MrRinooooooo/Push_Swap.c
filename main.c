#include "push_swap.h"

int main(int argc, char *argv[])
{
    static int  flags[5];
    int         *int_arr;
    t_list      *stack_a;
    t_list      *stack_b;
    float       disorder;

    stack_a = NULL;
    stack_b = NULL;

    flags_set_zero(flags);
    flags_parser(flags, argc, argv);
    int_arr = int_arr_parser(argc, argv, flags_num(flags));
    stack_a = list_arg_parser(int_arr, 3);
    print_stack(stack_a);
    /*
    errors_checker(int argc, char *argv[], int flags);
    arg_parser(int argc, char *argv[]);
    disorder = compute_disorder(stack a);
    */

    //RICORDASI FREE(INT_ARRAY) E FREE(stack)
    return(0);
}