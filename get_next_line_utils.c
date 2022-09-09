/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:37:41 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/08 22:53:56 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		{
			printf("new line found\n");
			return (1);
		}
		str++;
	}
	return (0);
}

char	*ft_strjoin(char *line, char *buff)
{
	char	*join;
	size_t	i;
	size_t	size;

	size = ft_strlen(line) + ft_strlen(buff) + 1;
	join = (char *) malloc(sizeof(char) * size);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (*line)
		*(join + i++) = *line++;
	while (*buff)
		*(join + i++) = *buff++;
	*(join + i) = '\0';
	return (join);
}