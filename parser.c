#include "push_swap.h"

int *int_arr_parser(int argc, char *argv[], int flags_n)
{
    int *arr;
    int i;
    int arr_len;

    i = 0;
    arr_len = argc - flags_n - 1;
    printf("CIAO3.1\n");
    arr = malloc(sizeof(int) * arr_len);
    /*if(!arr)
    {
        free(arr);
        print_error();
    }*/

    while (i < arr_len)
    {
        printf("CIAO3.2\n");
        arr[i] =  atoi_safe(argv[flags_n + 1]);
        i++;
        flags_n++;
    }
    return (arr);
}

t_list  *list_arg_parser(int arr[], int size)
{
    t_list *stack;
    t_list *new_node;

    stack = NULL;
    while (size > 0)
    {  
        size--;
        new_node = ft_lstnew(arr[size]);
        ft_lstadd_front(&stack, new_node);
    }
    return (stack);
}

void    free_stack(t_list **stack)
{
    t_list *next_node;

    if (!stack || !*stack)
        return;
    /*
    if (*stack->next)
        next_node = *stack->next;
    */
    while (*stack)
	{
		next_node = (*stack)->next;
		free(*stack);
        *stack = next_node;
	}
}