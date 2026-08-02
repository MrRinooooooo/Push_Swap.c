#include "push_swap.h"

int is_range_sorted_b(t_list *b, int size)
{
    if (!b || size <= 1)
        return (1);
    while (size > 1 && b && b->next)
    {
        if (b->rank < b->next->rank)
            return (0);
        b = b->next;
        size--;
    }
    return (1);
}

int is_range_sorted_a(t_list *a, int size)
{
    if (!a || size <= 1)
        return (1);
    while (size > 1 && a && a->next)
    {
        if (a->rank > a->next->rank)
            return (0);
        a = a->next;
        size--;
    }
    return (1);
}

int    partition_a(t_list **a, t_list **b, int size, int pivot, t_count *count)
{
    int pushed;
    int rotates;
    int total_stack_a;

    pushed = 0;
    rotates = 0;
    total_stack_a = stack_size(*a);
    printf("partition_a pivot=%d total_stack=%d\n", pivot, total_stack_a);
    while (size > 0 && *a)
    {
        if ((*a)->rank < pivot)
        {
            pb(b, a, count, 1);
            pushed++;
        }
        else
        {
            ra(a, count, 1);
            rotates++;
        }
        size--;
    }
    if (total_stack_a > size)
    {
        while (rotates > 0)
        {
            rra(a, count, 1);
            rotates--;
        }
    }
    return (pushed);
}

int    partition_b(t_list **a, t_list **b, int size, int pivot, t_count *count)
{
    int pushed;
    int rotates;
    int total_stack;

    pushed = 0;
    rotates = 0;
    total_stack = stack_size(*b);
    printf("partition_b pivot=%d total_stack=%d\n", pivot, total_stack);
    while(size > 0 && *b)
    {
        if ((*b)->rank > pivot)
        {
            pa(a, b, count, 1);
            pushed++;
        }
        else
        {
            rb(b, count, 1);
            rotates++;
        }
        size--;
    }
    if (total_stack > size)
    {
        while (rotates > 0)
        {
            rrb(b, count, 1);
            rotates--;
        }
    }
    return (pushed);
}

void sort_a(t_list **a, t_list **b, int size, int min, int max, t_count *count)
{
    int pivot;
    int pushed;

    printf("\nsort_a size=%d min=%d max=%d\n", size, min, max);
    print_stack(*a);
    printf("\n\n");
    if (size < 1 || is_range_sorted_a(*a, size))
        return;
    if (size == 2)
    {
        if ((*a)->rank > (*a)->next->rank)
            sa(a, count, 1);
        return;
    }
    pivot = (min + max) / 2;
    pushed = partition_a(a, b, size, pivot, count);
    if (pushed == 0 || pushed == size)
        return;
    sort_a(a, b, size - pushed, pivot, max, count);
    sort_b(a, b, pushed, min, pivot - 1, count);
}

void sort_b(t_list **a, t_list **b, int size, int min, int max, t_count *count)
{
    int pivot;
    int pushed;

    printf("\nsort_b size=%d min=%d max=%d\n", size, min, max);
    print_stack(*b);
    printf("\n\n");
    if (size < 1)
        return;
    if (is_range_sorted_b(*b, size))
    {
        while (size > 0)
        {
            pa(a, b, count, 1);
            size--;
        }
        return;
    }
    if (size == 2)
    {
        if ((*b)->rank < (*b)->next->rank)
            sb(b, count, 1);
        pa(a, b, count, 1);
        pa(a, b, count, 1);
        return;
    }
    pivot = (min + max) / 2;
    pushed = partition_b(a, b, size, pivot, count);
    //if (pushed == 0 || pushed == size)
    //    return;
    sort_a(a, b, pushed, pivot + 1, max, count);
    sort_b(a, b, size - pushed, min, pivot, count);
}

void complex_sort(t_list **a, t_list **b, int size, t_count *count)
{
    printf("complex_sort() size=%d\n", size);
    if (size <= 1)
        return;
    
    
    sort_a(a, b, size, 0, size - 1, count);
    
    printf("\n\n");
    print_stack(*a);
}