#include "push_swap.h"

int ps_strlen(char  *s1)
{
    int i;

    i = 0;
    if(!s1)
        return (0);
    while (s1[i])
        i++;
    return (i);
}

int ps_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			return (diff);
		}
		i++;
	}
	return (diff);
}

int	atoi_safe(const char *str)
{
	int		result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	if (*str == '-')
    {
		sign = -1;
	    str++;
    }
	if (*str < '0' || *str > '9')
		print_error();
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (sign == 1)
		{
			if (result > (INT_MAX - digit) / 10)
				print_error();
		}
		else
		{
			if (result > ((unsigned int)INT_MAX + 1 - digit) / 10)
				print_error();
		}
		result = result * 10 + digit;
		str++;
	}
	if (*str != '\0')
		print_error();
	return (result * sign);
}