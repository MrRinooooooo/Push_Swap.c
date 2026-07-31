#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_list
{
	int				value;
	int				rank;
	struct s_list	*next;
}					t_list;

typedef struct s_alg_vars
{
	int     chunk_size;
    int     chunk_min;
    int     chunk_max;
    int     chunk_to_push;
    int     a_size;
    int     b_size;
}					t_vars;

typedef struct s_counters
{
	int     sa;
    int     sb;
    int     ss;
    int     pa;
    int     pb;
    int     ra;
    int     rb;
    int     rr;
    int     rra;
    int     rrb;
    int     rrr;
}					t_count;

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <limits.h>
// TESTING
# include <stdio.h>

// alg_adaptive.c
// alg_complex.c
// alg_medium_utils.c
int     find_min_index_chunk(t_list *stack, t_vars *vars);
void    move_to_top_chunk(t_list **stack_a, t_vars *vars, t_count *count);
int    	find_max_index(t_list *stack);
void    move_to_top_b(t_list **b, t_vars *vars, t_count *count);
void    update_vars(t_vars *vars, int size);
// alg_medium.c
void    exec_medium(t_list **stack_a, t_list **stack_b, int size, t_count *count);
void	init_vars(t_vars *vars, int size);
int		calculate_chunk(int size);
// alg_simple.c
void    simple_sort(t_list **a, t_list **b, t_count *count);
int     is_sorted(t_list *stack);
void    move_to_top(t_list **a, t_count *count);
int     find_min_index(t_list *stack);
int     stack_size(t_list *stack);
// bench.c
void    print_bench(t_count count, float disorder, int *flags, char *strategy);
void    print_disorder(float disorder);
void    print_strategy(int *flags, char *strategy);
void    init_counts(t_count *count);
// debugger.c
void	print_stack(t_list *lst);
void	print_stack_rank(t_list *lst);
void    print_vars(t_vars *vars);
// disorder.c
float	compute_disorder(int array[], int arraylen);
// errors_checker.c
void    print_error();
// flags.c
void    flags_set_zero(int flags[]);
void    set_flags(int flags[], int i);
void    flags_parser(int flags[], int argc, char *argv[]);
int     flags_num(int flags[]);
// list_utils.c
t_list	*ps_lstnew(int value, int rank);
void	ps_lstadd_front(t_list **lst, t_list *new);
void	ps_lstdelfirst(t_list **lst);
// operations_push_swap.c
void    sa(t_list **lst, t_count *count);
void    sb(t_list **lst, t_count *count);
void    pa(t_list **stack_a, t_list **stack_b, t_count *count);
void    pb(t_list **stack_b, t_list **stack_a, t_count *count);
// operations_reverse_rotate.c
void    rra(t_list **stack_a, t_count *count);
void    rrb(t_list **stack_b, t_count *count);
// operations_rotate.c
void    ra(t_list **stack_a, t_count *count);
void    rb(t_list **stack_b, t_count *count);
// parser.c
int 	*int_arr_parser(int argc, char *argv[], int flags_n);
void	assign_rank(int *arr, int *rank_arr, int size);
t_list	*list_arg_parser(int arr[], int size);
void    free_stack(t_list **stack);
// printf_stderr.c
int     printf_stderr(const char *s, ...);
int     ft_handle_format(char c, va_list args);
int     ft_putunbr(unsigned int n);
int     ft_putchar(char c);
int     ft_putstr(char *s);
// strings_utils.c
int 	ps_strlen(char  *s1);
int		ps_strcmp(const char *s1, const char *s2);
int		atoi_safe(const char *str);
// ------------------------------------------- BONUS
/*
// get_next_line.c
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
// get_next_line_utils.c
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_split(char *str);
char	*get_ret_line(char *s);
*/
#endif