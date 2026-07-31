#include "push_swap.h"

    /*STRUCT vars
    int     chunk_size;
    int     chunk_min;
    int     chunk_max;
    int     chunk_to_push;
    int     a_size;
    int     b_size;*/

/*void    exec_medium(t_list **stack_a, t_list **stack_b, int size)
{
    t_vars  vars;
    int     i;
    int     debug_ciclo = 0;

    init_vars(&vars, size);
    printf("\nSTARTING VARS:\n");
    print_vars(&vars);
    while (*stack_a != NULL)
    {
        i = find_min_index_chunk(*stack_a, &vars);
        move_to_top_chunk(stack_a, &vars);
        /*if (stack_b && *stack_b && (*stack_b)->next)
        {
            while(((*stack_a)->rank < (*stack_b)->rank) && (*stack_b)->next)
            {
            rb(stack_b);
            if ((*stack_b)->rank < (*stack_b)->next->rank)
                sb(stack_b);
            }
        //}

        pb(stack_b, stack_a);
        vars.b_size++;
        vars.a_size--;
        vars.chunk_to_push--;

        //DEBUG
        printf("\nMODIFICHE VARS CICLO %d:\n", debug_ciclo);
        print_vars(&vars);
        debug_ciclo++;
        //

        if (vars.chunk_to_push == 0 && vars.chunk_max != (size - 1))
        {
            if ((vars.chunk_max + (vars.chunk_size * 2)) > (size - 1) )
            {
                vars.chunk_max = size - 1;
		        vars.chunk_min += vars.chunk_size;
            }
            else
            {
            	vars.chunk_min += vars.chunk_size;
            	vars.chunk_max += vars.chunk_size;
            }
        	vars.chunk_to_push = vars.chunk_max - vars.chunk_min + 1;
        }
    }
    while (vars.b_size > 0)
    {
	move_to_top_b(stack_b);
        pa(stack_a, stack_b);
        vars.a_size++;
        vars.b_size--;
    }
    //DEBUG
    print_vars(&vars);
}
*/
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
    printf("\nSIZE DENTRO CALCULATE CHUNK = %d\n", size);
    return (i);
}
/*
int main (void)
{

    //int rad;

    //rad = calculate_chunk(24);
    //printf("%d", rad);

    t_vars vars;
    init_vars(&vars, 24);

    printf("%d", vars.chunk_size);

    return (0);
}*/

int    find_min_index_chunk(t_list *stack, t_vars *vars)
{
    int min_pos;
    int pos;
    t_list *current;

    min_pos = 100000;
    pos = 0;
    current = stack;
    while (current->next != NULL)
    {
        if (current->rank >= vars->chunk_min && current->rank <= vars->chunk_max)
        {
            if ((vars->a_size - pos) < min_pos)
                min_pos = pos;
        }
        current = current->next;
        pos++;
    }
    return (min_pos);
}

void move_to_top_chunk(t_list **stack_a, t_vars *vars)
{
    int min_pos;
    int moves;

    min_pos = find_min_index_chunk(*stack_a, vars);
    if (min_pos <= (vars->a_size / 2))
    {
        while (min_pos > 0)
        {
            ra(stack_a);
            min_pos--;
        }
    }
    else
    {
        moves = vars->a_size - min_pos;
        while (moves > 0)
        {
            rra(stack_a);
            moves--;
        }
    }
}
// DEBUG
void    print_vars(t_vars *vars)
{
    printf("\nchunk_size =\t%d", vars->chunk_size);
    printf("\nchunk_min =\t%d", vars->chunk_min);
    printf("\nchunk_max =\t%d", vars->chunk_max);
    printf("\nchunk_to_push =\t%d", vars->chunk_to_push);
    printf("\na_size =\t%d", vars->a_size);
    printf("\nb_size =\t%d", vars->b_size);
    printf("\n");
}

// -------------------------

int    find_max_index(t_list *stack)
{
    int max;
    int max_pos;
    int pos;
    t_list *current;

    max = stack->rank;
    max_pos = 0;
    pos = 0;
    current = stack;
    while (current->next != NULL)
    {
        current = current->next;
        pos++;
        if (current->rank > max)
        {
            max = current->rank;
            max_pos = pos;
        }
    }
    return (max_pos);
}

void move_to_top_b(t_list **b)
{
    int max_pos;
    int size;
    int moves;

    max_pos = find_max_index(*b);
    size = stack_size(*b);
    if (max_pos <= size / 2)
    {
        while (max_pos > 0)
        {
            rb(b);
            max_pos--;
        }
    }
    else
    {
        moves = size - max_pos;
        while (moves > 0)
        {
            rrb(b);
            moves--;
        }
    }
}

void    exec_medium(t_list **stack_a, t_list **stack_b, int size)
{
    t_vars  vars;
    int     i;
    int     debug_ciclo = 0;

    init_vars(&vars, size);
    while (*stack_a != NULL)
    {
        i = find_min_index_chunk(*stack_a, &vars);
        move_to_top_chunk(stack_a, &vars);

        pb(stack_b, stack_a);
	//DEBUG
        printf("\nMODIFICHE VARS CICLO %d:\n", debug_ciclo);
        print_vars(&vars);
        debug_ciclo++;
        //
        update_vars(&vars, size);
        /*
        vars.b_size++;
        vars.a_size--;
        vars.chunk_to_push--;
        if (vars.chunk_to_push == 0 && vars.chunk_max != (size - 1))
        {
            if ((vars.chunk_max + (vars.chunk_size * 2)) > (size - 1) )
            {
                vars.chunk_max = size - 1;
		        vars.chunk_min += vars.chunk_size;
            }
            else
            {
            	vars.chunk_min += vars.chunk_size;
            	vars.chunk_max += vars.chunk_size;
            }
        vars.chunk_to_push = vars.chunk_max - vars.chunk_min + 1;
        }
        */
    }
    while (vars.b_size > 0)
    {
	    move_to_top_b(stack_b);
        pa(stack_a, stack_b);
        vars.a_size++;
        vars.b_size--;
    }
}

void    update_vars(t_vars *vars, int size)
{
    vars->b_size++;
    vars->a_size--;
    vars->chunk_to_push--;
    if (vars->chunk_to_push == 0 && vars->chunk_max != (size - 1))
    {
        if ((vars->chunk_max + (vars->chunk_size * 2)) > (size - 1) )
        {
            vars->chunk_max = size - 1;
		    vars->chunk_min += vars->chunk_size;
        }
        else
        {
            vars->chunk_min += vars->chunk_size;
            vars->chunk_max += vars->chunk_size;
        }
    vars->chunk_to_push = vars->chunk_max - vars->chunk_min + 1;
    }
}