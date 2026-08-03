#include "push_swap.h"

int	*int_arr_parser(int argc, char *argv[], int flags_n)
{
	int	*arr;
	int	i;
	int	arr_len;

	i = 0;
	arr_len = argc - flags_n - 1;
	arr = malloc(sizeof(int) * arr_len);
	if (!arr)
	{
		free(arr);
		print_error();
	}
	while (i < arr_len)
	{
		arr[i] = atoi_safe(argv[flags_n + 1], arr);
		i++;
		flags_n++;
	}
	return (arr);
}

void	assign_rank(int *arr, int *rank_arr, int size)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (i < size)
	{
		count = 0;
		j = 0;
		while (j < size)
		{
			if (arr[j] < arr[i])
				count++;
			j++;
		}
		rank_arr[i] = count;
		i++;
	}
}

t_list	*list_arg_parser(int arr[], int size)
{
	t_list	*stack;
	t_list	*new_node;
	int		*rank_arr;

	rank_arr = malloc(sizeof(int) * size);
	if (!rank_arr)
		return (NULL);
	assign_rank(arr, rank_arr, size);
	stack = NULL;
	while (size > 0)
	{
		size--;
		new_node = ps_lstnew(arr[size], rank_arr[size]);
		if (!new_node)
		{
			free(rank_arr);
			return (NULL);
		}
		ps_lstadd_front(&stack, new_node);
	}
	free(rank_arr);
	return (stack);
}

void	free_stack(t_list **stack)
{
	t_list	*next_node;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		next_node = (*stack)->next;
		free(*stack);
		*stack = next_node;
	}
}
