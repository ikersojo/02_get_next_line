/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:37:41 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/27 10:14:31 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(join + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j))
		*(join + i++) = *(s2 + j++);
	*(join + i) = '\0';
	free((char *)s1);
	free((char *)s2);
	return (join);
}

int	ft_isline(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL || len == 0 || ft_strlen(s) < (size_t)start)
		return (NULL);
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	s = s + start;
	i = 0;
	while (*s && i < len)
		*(sub + i++) = *s++;
	*(sub + i) = '\0';
	return (sub);
}
