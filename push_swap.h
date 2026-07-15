#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_list
{
	void			*content;
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
void    n_flags(int flags[], int argc, char *argv[]);
// errors_checker.c
void    print_error();
// strings_utils.c
int 	ps_strlen(char  *s1);
int		ps_strcmp(const char *s1, const char *s2);
int		atoi_safe(const char *str);
// push_swap_functions.c
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