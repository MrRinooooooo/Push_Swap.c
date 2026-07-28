#include "push_swap.h"

int    find_min_index(t_list *stack)
{
    int min;
    int min_pos;
    int pos;
    t_list *current;

    min = stack->value;
    min_pos = 0;
    pos = 0;
    current = stack;
    while (current->next != NULL)
    {
        current = current->next;
        pos++;
        if (current->value < min)
        {
            min = current->value;
            min_pos = pos;
        }
        return (min_pos);
    }
}

void move_to_top(t_list **a)
{
    int min_pos;
    int size;
    int moves;

    min_pos = find_min_index(*a);
    size = stack_size(*a); \\??
    if (min_pos <= size / 2)
    {
        while (min_pos > 0)
        {
            ra(a);
            min_pos--;
        }
    }
    else
    {
        moves = size - min_pos;
        while (moves > 0)
        {
            rra(stack);
            moves--;
        }
    }
}