#include "push_swap.h"

int    partition_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
    int pushed;
    int rotates;
    int total_stack_a;
    int remaining;

    pushed = 0;
    rotates = 0;
    remaining = range->size;
    total_stack_a = stack_size(*a);
    printf("partition_a pivot=%d total_stack=%d\n", range->pivot, total_stack_a);
    while (remaining > 0 && *a)
    {
        if ((*a)->rank < range->pivot)
        {
            pb(b, a, count, 1);
            pushed++;
        }
        else
        {
            ra(a, count, 1);
            rotates++;
        }
        remaining--;
    }
    if (total_stack_a > remaining)
    {
        while (rotates > 0)
        {
            rra(a, count, 1);
            rotates--;
        }
    }
    return (pushed);
}

int    partition_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
    int pushed;
    int rotates;
    int total_stack;
    int remaining;

    pushed = 0;
    rotates = 0;
    remaining = range->size;
    total_stack = stack_size(*b);
    printf("partition_b pivot=%d total_stack=%d\n", range->pivot, total_stack);
    while (remaining > 0 && *b)
    {
        if ((*b)->rank > range->pivot)
        {
            pa(a, b, count, 1);
            pushed++;
        }
        else
        {
            rb(b, count, 1);
            rotates++;
        }
        remaining--;
    }
    if (total_stack > remaining)
    {
        while (rotates > 0)
        {
            rrb(b, count, 1);
            rotates--;
        }
    }
    return (pushed);
}

void sort_a(t_list **a, t_list **b, t_range *range, t_count *count)
{
    t_range part;
    t_range next;
    int     pivot;
    int     pushed;

    printf("\nsort_a size=%d min=%d max=%d\n", range->size, range->min, range->max);
    print_stack(*a);
    printf("\n\n");
    if (range->size < 1 || is_range_sorted_a(*a, range->size))
        return;
    if (range->size == 2)
    {
        if ((*a)->rank > (*a)->next->rank)
            sa(a, count, 1);
        return;
    }
    pivot = range->min + range->size / 2;
    part.size = range->size;
    part.pivot = pivot;
    pushed = partition_a(a, b, &part, count);
    if (pushed == 0 || pushed == range->size)
        return;
    next.size = range->size - pushed;
    next.min = pivot;
    next.max = range->max;
    sort_a(a, b, &next, count);
    next.size = pushed;
    next.min = range->min;
    next.max = pivot - 1;
    sort_b(a, b, &next, count);
}

void sort_b(t_list **a, t_list **b, t_range *range, t_count *count)
{
    t_range part;
    t_range next;
    int     pivot;
    int     pushed;
    int     remaining;

    printf("\nsort_b size=%d min=%d max=%d\n", range->size, range->min, range->max);
    print_stack(*b);
    printf("\n\n");
    if (range->size < 1)
        return;
    if (is_range_sorted_b(*b, range->size))
    {
        remaining = range->size;
        while (remaining > 0)
        {
            pa(a, b, count, 1);
            remaining--;
        }
        return;
    }
    if (range->size == 2)
    {
        if ((*b)->rank < (*b)->next->rank)
            sb(b, count, 1);
        pa(a, b, count, 1);
        pa(a, b, count, 1);
        return;
    }
    pivot = range->min + range->size / 2;
    part.size = range->size;
    part.pivot = pivot;
    pushed = partition_b(a, b, &part, count);
    next.size = pushed;
    next.min = pivot + 1;
    next.max = range->max;
    sort_a(a, b, &next, count);
    next.size = range->size - pushed;
    next.min = range->min;
    next.max = pivot;
    sort_b(a, b, &next, count);
}

void complex_sort(t_list **a, t_list **b, int size, t_count *count)
{
    t_range range;

    printf("complex_sort() size=%d\n", size);
    if (size <= 1)
        return;
    range.size = size;
    range.min = 0;
    range.max = size - 1;
    range.pivot = 0;
    sort_a(a, b, &range, count);
    printf("\n\n");
    print_stack(*a);
}