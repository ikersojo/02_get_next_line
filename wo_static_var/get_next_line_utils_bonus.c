/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:37:41 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/15 08:37:34 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_isline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strappend(char *line, char *buff)
{
	char	*append;
	size_t	i;
	size_t	size;

	size = ft_strlen(line) + ft_strlen(buff) + 1;
	append = (char *) malloc(sizeof(char) * size);
	if (append == NULL)
		return (NULL);
	i = 0;
	while (*line)
		*(append + i++) = *line++;
	while (*buff)
		*(append + i++) = *buff++;
	*(append + i) = '\0';
	return (append);
}
