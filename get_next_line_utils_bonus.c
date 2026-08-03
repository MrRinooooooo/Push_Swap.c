/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_next_line_utils.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abenelli <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/06/30 17:02:09 by abenelli		   #+#	  #+#			  */
/*	 Updated: 2026/07/01 14:49:48 by abenelli		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (!s)
		return (0);
	ch = (unsigned char) c;
	while (1)
	{
		if ((unsigned char)*s == ch)
			return (1);
		if (*s == '\0')
			return (0);
		s++;
	}
}

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = ps_strlen((char *) str);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		len_s1;
	int		len_s2;	
	int		i;
	int		j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	len_s1 = ps_strlen(s1);
	len_s2 = ps_strlen(s2);
	ret = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ret)
		return (free(s1), NULL);
	i = 0;
	while (i < len_s1)
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (free(s1), ret);
}

char	*ft_split(char *str)
{
	int		i;
	char	*ret;
	int		ret_len;
	int		j;

	if (!str || *str == '\0')
		return (free(str), NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	ret_len = ps_strlen(str);
	ret = malloc(sizeof(char) * (ret_len - i + 1));
	if (!ret)
		return (free(str), NULL);
	j = 0;
	while (++i <= ret_len)
		ret[j++] = str[i];
	ret[j] = '\0';
	free(str);
	return (ret);
}

char	*get_ret_line(char *str)
{
	int		i;
	char	*ret;

	if (!str || *str == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		ret = malloc(sizeof(char) * (i + 2));
		if (!ret)
			return (free(str), NULL);
		ret[i + 1] = '\0';
		while (i >= 0)
		{
			ret[i] = str[i];
			i--;
		}
		return (ret);
	}
	return (ft_strdup(str));
}
