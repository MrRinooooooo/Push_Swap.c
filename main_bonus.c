#include "push_swap.h"

int	main(int argc, char *argv[])
{
	char		*line;
	int			*int_arr;
	t_list		*stack_a;
	t_list		*stack_b;
	t_count		count;

	init_counts(&count);
	stack_b = NULL;
	if (argc == 1)
		return (0);
	int_arr = int_arr_parser(argc, argv, 0);
	stack_a = list_arg_parser(int_arr, (argc - 1));
	line = get_next_line(0);
	while (line != NULL)
	{
		checker_ops(&stack_a, &stack_b, line, count);
		free(line);
		line = get_next_line(0);
	}
	checker(&stack_a, &stack_b);
	free(int_arr);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	ssize_t		bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(str), str = NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(str), NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			break ;
		buffer[bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	line = get_ret_line(str);
	str = ft_split(str);
	free(buffer);
	return (line);
}

void	checker_ops(t_list **a, t_list **b, char *ops, t_count count)
{
	if (ps_strcmp(ops, "sa\n") == 0)
		sa(a, &count, 0);
	else if (ps_strcmp(ops, "sb\n") == 0)
		sb(b, &count, 0);
	else if (ps_strcmp(ops, "ss\n") == 0)
		ss(a, b, &count, 0);
	else if (ps_strcmp(ops, "pa\n") == 0)
		pa(a, b, &count, 0);
	else if (ps_strcmp(ops, "pb\n") == 0)
		pb(b, a, &count, 0);
	else if (ps_strcmp(ops, "rra\n") == 0)
		rra(a, &count, 0);
	else if (ps_strcmp(ops, "rrb\n") == 0)
		rrb(b, &count, 0);
	else if (ps_strcmp(ops, "rrr\n") == 0)
		rrr(a, b, &count, 0);
	else if (ps_strcmp(ops, "ra\n") == 0)
		ra(a, &count, 0);
	else if (ps_strcmp(ops, "rb\n") == 0)
		rb(b, &count, 0);
	else if (ps_strcmp(ops, "rr\n") == 0)
		rr(a, b, &count, 0);
	else
		print_error_free_stack(a, b);
}

void	checker(t_list **stack_a, t_list **stack_b)
{
	if (is_sorted(*stack_a) && !*stack_b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}
