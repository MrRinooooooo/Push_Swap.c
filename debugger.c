#include "push_swap.h"

void	print_stack(t_list *lst)
{
	while (lst)
	{
		printf("%d\n", lst->value);
		lst = lst->next;
	}
}

void	print_stack_rank(t_list *lst)
{
	while (lst)
	{
		printf("Value: %d\t\tRank: %d\n", lst->value, lst->rank);
		lst = lst->next;
	}
}

void    print_vars(t_vars *vars)
{
    printf("\nchunk_size =\t%d", vars->chunk_size);
    printf("\nchunk_min =\t%d", vars->chunk_min);
    printf("\nchunk_max =\t%d", vars->chunk_max);
    printf("\nchunk_to_push =\t%d", vars->chunk_to_push);
    printf("\na_size =\t%d", vars->a_size);
    printf("\nb_size =\t%d", vars->b_size);
    printf("\n");
}

void	print_flags(int *flags)
{
	printf("\nFlag [0] --BENCH	=  %d", flags[0]);
	printf("\nFlag [1] --SIMPLE  	=  %d", flags[1]);
    printf("\nFlag [2] --MEDIUM  	=  %d", flags[2]);
    printf("\nFlag [3] --COMPLEX 	=  %d", flags[3]);
    printf("\nFlag [4] --ADAPTIVE 	=  %d", flags[4]);
    printf("\nFlag [5] --CUSTOM  	=  %d", flags[5]);
}