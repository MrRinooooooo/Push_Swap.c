#include "push_swap.h"

void	print_bench(t_count count, float disorder, int *flags, char *strategy)
{
	int		total_ops;

	total_ops = 0;
	total_ops = count.sa + count.sb + count.ss + count.pa + count.pb
		+ count.ra + count.rb + count.rr + count.rra + count.rrb + count.rrr;
	printf_stderr("[bench] disorder:  ");
	print_disorder(disorder);
	printf_stderr("\n[bench] strategy:  ");
	print_strategy(flags, strategy);
	printf_stderr("\n[bench] total_ops:  %d", total_ops);
	printf_stderr("\n[bench] sa:  %d  sb:  %d  ss:  %d  pa:  %d  pb:  %d",
		count.sa, count.sb, count.ss, count.pa, count.pb);
	printf_stderr("\n[bench] ra:  %d  rb  %d  rr:  %d  "
		"rra:  %d  rrb:  %d  rrr:  %d",
		count.ra, count.rb, count.rr, count.rra, count.rrb, count.rrr);
}

void	print_disorder(float disorder)
{
	int	int_dis;
	int	first;
	int	second;

	int_dis = disorder * 10000;
	first = int_dis / 100;
	second = int_dis % 100;
	if (int_dis == 10000)
		printf_stderr("100.00%%");
	else if (int_dis < 10)
		printf_stderr("0.0%d%%", second);
	else if (int_dis < 100)
	{
		if (second < 10)
			printf_stderr("0.0%d%%", second);
		else
			printf_stderr("0.%d%%", second);
	}
	else
	{
		if (second < 10)
			printf_stderr("%d.0%d%%", first, second);
		else
			printf_stderr("%d.%d%%", first, second);
	}
}

void	print_strategy(int *flags, char *strategy)
{
	if (flags[4] == 1)
	{
		printf_stderr("Adaptive / ");
	}
	else if (flags[1] == 1)
	{
		printf_stderr("Simple / ");
	}
	else if (flags[2] == 1)
	{
		printf_stderr("Medium / ");
	}
	else
	{
		printf_stderr("Complex / ");
	}
	printf_stderr("%s", strategy);
}

void	init_counts(t_count *count)
{
	count->sa = 0;
	count->sb = 0;
	count->ss = 0;
	count->pa = 0;
	count->pb = 0;
	count->ra = 0;
	count->rb = 0;
	count->rr = 0;
	count->rra = 0;
	count->rrb = 0;
	count->rrr = 0;
}
