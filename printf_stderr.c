#include "push_swap.h"

int	printf_stderr(const char *s, ...)
{
	va_list			args;
	int				ret;

	ret = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			ret += ft_handle_format(*s, args);
		}
		else
			ret += ft_putchar(*s);
		s++;
	}
	va_end(args);
	return (ret);
}

int	ft_handle_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'd')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (c == '%')
		write(2, "%", 1);
	return (0);
}

int	ft_putunbr(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n >= 10)
		ret += ft_putunbr(n / 10);
	ret += ft_putchar((n % 10) + '0');
	return (ret);
}

int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	slen;

	if (!s)
	{
		write(2, "(null)", 6);
		return (6);
	}
	slen = ps_strlen(s);
	write(2, s, slen);
	return (slen);
}
