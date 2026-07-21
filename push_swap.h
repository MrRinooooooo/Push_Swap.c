#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_list
{
	int				value;
	struct s_list	*next;
}					t_list;

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
#include <limits.h>    // atoi_safe
// TESTING
# include <stdio.h>

// flags.c
void    flags_set_zero(int flags[]);
void    set_flags(int flags[], int i);
void    flags_parser(int flags[], int argc, char *argv[]);
int     flags_num(int flags[]);
// errors_checker.c
void    print_error();
// parser.c
int 	*int_arr_parser(int argc, char *argv[], int flags_n);
t_list	*list_arg_parser(int arr[], int size);
void    free_stack(t_list **stack);
// strings_utils.c
int 	ps_strlen(char  *s1);
int		ps_strcmp(const char *s1, const char *s2);
int		atoi_safe(const char *str);
// list_utils.c
t_list	*ft_lstnew(int value);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	print_stack(t_list *lst);
void	lstdelfirst(t_list **lst);
// push_swap_functions.c
int sa(t_list **lst);
int sb(t_list **lst);
// rotate_functions.c
// reverse_rotate_functions.c
// alg_simple.c
// alg_medium.c
// alg_complex.c
// alg_adaptive.c


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