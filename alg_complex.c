#include "push_swap.h"

int    partition_a(t_list **a, t_list **b, int size, int pivot, t_count *count)
{
    int pushed;

    pushed = 0;
    while (size > 0 && *a)
    {
        if ((*a)->rank < pivot)
        {
            pb(b, a, count);
            pushed++;
        }
        else
            ra(a, count);
        size--;
    }
    return (pushed);
}

void    partition_b(t_list **a, t_list **b, int size, int pivot, t_count *count)
{
    int pushed;

    pushed = 0;
    while(size > 0 && *b)
    {
        if ((*b)->rank >= pivot)
        {
            pa(a, b, count);
            pushed++;
        }
        else
            rb(b, count);
        size--;
    }
    return (pushed);
}

void sort_a(t_list **a, t_list **b, int size, int min, int max, t_count *count)
{
    int pivot;
    int pushed;

    if (size <= 1 || is_sorted(*a))
        return;
    pivot = (min + max) / 2;
    pushed = partition_a(a, b, size, pivot, count);
    sort_a(a, b, size - pushed, pivot, max, count);
    sort_b(a, b, pushed, min, pivot - 1, count);
}

void sort_b(t_list **a, t_list **b, int size, int min, int max, t_count *count)
{
    int pivot;
    int pushed;

    if (size <= 1)
        return;
     pivot = (min + max) / 2;
    pushed = partition_b(a, b, size, pivot, count);
    sort_a(a, b, pushed, pivot, max, count);
    sort_b(a, b, size - pushed, min, pivot - 1, count);
}

void complex_sort(t_list **a, t_list **b, int size, t_count *count)
{
    if (size <= 1)
        return;
    sort_a(a, b, size, 0, size - 1, count);
}