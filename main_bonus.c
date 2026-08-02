#include "push_swap.h"

int main(int argc, char *argv[])
{
	//int     fd;
	char        *line;
    int         *int_arr;
    t_list      *stack_a;
    t_list      *stack_b;
    int         size;

    stack_b = NULL;
    if (argc == 1)
        return (0);
    //flags_parser(flags, argc, argv);
    int_arr = int_arr_parser(argc, argv, 0);
    size = argc - 1;
    stack_a = list_arg_parser(int_arr, size);


	//fd = open("test_fd1.txt", O_RDONLY);
	while ((line = get_next_line(0)) != NULL)
	{
        checker_ops(&stack_a, &stack_b, line);
		free(line);
	}
    checker(&stack_a, &stack_b);
    print_stack(stack_a);
	//close(fd);
    //FREEEEEEEEEEEEEEEEEEEEE
	return (0);
}


char    *get_next_line(int fd)
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

void    checker_ops(t_list **a, t_list **b, char *ops)
{
    t_count count;

    if (ps_strcmp(ops, "sa"))
        sa(a, &count, 0);
    else if (ps_strcmp(ops, "sb"))
        sb(b, &count, 0);
    else if (ps_strcmp(ops, "ss"))
        ss(a, b, &count, 0);
    else if (ps_strcmp(ops, "pa"))
        pa(a, b, &count, 0);
    else if (ps_strcmp(ops, "pb"))
        pb(b, a, &count, 0);
    else if (ps_strcmp(ops, "rra"))
        rra(a, &count, 0);
    else if (ps_strcmp(ops, "rrb"))
        rrb(b, &count, 0);
    else if (ps_strcmp(ops, "rrr"))
        rrr(a, b, &count, 0);
    else if (ps_strcmp(ops, "ra"))
        ra(a, &count, 0);
    else if (ps_strcmp(ops, "rb"))
        rb(a, &count, 0);
    else if (ps_strcmp(ops, "rr"))
        rr(a, b, &count, 0);
}

void    checker(t_list **stack_a, t_list **stack_b)
{
    if (is_sorted(*stack_a) && !*stack_b)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);
}