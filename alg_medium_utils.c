#include "push_swap.h"

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

int     find_max_index(t_list *stack)
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

void    move_to_top_b(t_list **b, t_vars *vars)
{
    int max_pos;
    int moves;

    max_pos = find_max_index(*b);
    if (max_pos <= vars->b_size / 2)
    {
        while (max_pos > 0)
        {
            rb(b);
            max_pos--;
        }
    }
    else
    {
        moves = vars->b_size - max_pos;
        while (moves > 0)
        {
            rrb(b);
            moves--;
        }
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