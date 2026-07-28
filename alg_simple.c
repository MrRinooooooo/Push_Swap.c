#include "push_swap.h"

int stack_size(t_list *stack)
{
    int     size;
    t_list  *current;

    size = 0;
    current = stack;

    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return (size);
}

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
    }
    return (min_pos);
}

void move_to_top(t_list **a)
{
    int min_pos;
    int size;
    int moves;

    min_pos = find_min_index(*a);
    size = stack_size(*a);
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
            rra(a);
            moves--;
        }
    }
}

int is_sorted(t_list *stack)
{
    t_list *current;
    
    if (stack == NULL || stack->next == NULL)
        return (1);

    current = stack;
    while (current->next != NULL)
    {
        if (current->value > current->next->value)
            return (0);

        current = current->next;
    }
    return (1);
}

void simple_sort(t_list **a, t_list **b)
{
    if (is_sorted(*a))
        return;
    while (*a != NULL)
    {
        move_to_top(a);
        pb(a, b);
    }
    while (*b != NULL)
        pa(a, b);
}