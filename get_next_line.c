/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:38:02 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/08 23:16:25 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*read_buffer(size_t size, int fd)
{
	char	*buff;
	size_t	i;
	char	c;

	buff = (char *) malloc(sizeof(char) * (size + 1));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (read(fd, &c, 1) > 0 && i < size)
	{
		*(buff + i++) = c;
		if (c == '\n')
			break ;
	}
	*(buff + i) = '\0';
	printf("buff: %s", buff);
	return (buff);
}

char	*get_line(size_t size, int fd)
{
	char	*line;
	char	*buff;

	line = NULL;
	while (1)
	{
		buff = read_buffer(size, fd);
		line = ft_strjoin(line, buff);
		if (ft_isline(buff))
		{
			free(buff);
			break ;
		}
	}
	if (buff == NULL || line == NULL)
	{
		free(buff);
		free(line);
		return (NULL);
	}
	return (line);
}

/* DESCRIPTION:
The get_next_line() function return the next line from the content on file
pointed by fd. Starting from the first line, subsecuent calls the function
(in the same program, e.g. using a loop) will return the following line of
the file, until the EOF. A line ends with \n or EOF.
The function returns the string of the next line. In case of error or if
there is nothing to read, the function will return NULL.
Both a file and stdin (i.e. fd = 0) have to work.
The function will read BUFFER_SIZE bytes each attempt (defined as
compilation flag).
The function should be protected against reading binary files.
-----------------------------------------------------------------------------*/
char	*get_next_line(int fd)
{
	char	*line;

	// if new file, allocate element in struct or array?
	line = get_line(BUFFER_SIZE, fd);
	if (line == NULL)
		return (NULL);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	char	*line;
	int		i;

	fd1 = open("test0.txt", O_RDONLY);
	if (fd1 == -1)
		return (0);
	i = 0;
	while (i < 3)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		i++;
	}
	return (0);
}
