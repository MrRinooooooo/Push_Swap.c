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

    if (argc == 1)
        return (0);
    flags_set_zero(flags);
    flags_parser(flags, argc, argv);
    int_arr = int_arr_parser(argc, argv, flags_num(flags));
    stack_a = list_arg_parser(int_arr, 2);
    print_stack(stack_a);
    //free_stack(&stack_a);
    sa(&stack_a);
    sa(&stack_a);
    //DEBUG
    int count_a;
    count_a = sa(&stack_a);
    lstdelfirst(&stack_b);
    print_stack(stack_a);
    printf("\n SA: %i", count_a);
    /*
    errors_checker(int argc, char *argv[], int flags);
    arg_parser(int argc, char *argv[]);
    disorder = compute_disorder(stack a);
    */
    //RICORDARSI DI SOSTITUIRE TUTTI I PRINTF!!!!!!!!!!!!!
    //RICORDASI FREE(INT_ARRAY) E FREE(stack)
    return(0);
}