#include "push_swap.h"

    /*STRUCT vars
    int     chunk_size;
    int     chunk_min;
    int     chunk_max;
    int     chunk_to_push;
    int     a_size;
    int     b_size;*/

void    exec_medium(t_list **stack_a, t_list **stack_b, int size)
{
    t_vars  vars;
    int     i;

    init_vars(&vars, size);
    while (*stack_a != NULL)
    {
        i = find_min_index_chunk(*stack_a, &vars);
        move_to_top_chunk(stack_a, &vars);
        pb(stack_b, stack_a);
        update_vars(&vars, size);
    }
    while (vars.b_size > 0)
    {
	    move_to_top_b(stack_b, &vars);
        pa(stack_a, stack_b);
        vars.a_size++;
        vars.b_size--;
    }
}

void    init_vars(t_vars *vars, int size)
{
    vars->chunk_size = calculate_chunk(size);
    vars->chunk_min = 0;
    vars->chunk_max = vars->chunk_size -1;
    vars->chunk_to_push = vars->chunk_size;
    vars->a_size = size;
    vars->b_size = 0;
}

int calculate_chunk(int size)
{
    int chunk_size;
    int i;

    i = 1;
    chunk_size = 1;
    while (chunk_size <= size)
    {
        chunk_size = i * i;
        i++;
    }
    i -= 2;
    return (i);
}