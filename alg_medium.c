#include "push_swap.h"
/*
void    exec_medium(t_list **stack_a, t_list **stack_b, int size)
{
     STRUCT
    int     chunk_size;
    int     chunk_min;
    int     chunk_max;
    int     chunk_to_push;
    int     a_size;
    int     b_size;
    
    t_vars  vars;
    int     i;
    t_list  *shift_a;
    t_list  *shift_b;

    init_vars(&vars, size);
}
*/
void    init_vars(t_vars *vars, int size)
{
    vars->chunk_size = calculate_chunk(size);
    vars->chunk_min = 0;
    vars->chunk_max = vars->chunk -1;
    vars->chunk_to_push = vars->chunk;
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
    i--;
    return (i);
}

int main (void)
{
    /*
    int rad;

    rad = calculate_chunk(24);
    printf("%d", rad);
    */
    t_vars vars;
    init_vars(&vars, 24);

    printf("%d", vars.chunk_size);
    
    return (0);
}