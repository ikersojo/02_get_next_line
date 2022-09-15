/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:38:02 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/15 18:19:51 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#define FD_LIMIT 1024
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#if (BUFFER_SIZE > 1000)
# undef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

static void	ft_read_buffer(int fd, char **holder, int *bytes)
{
	char	*buff;

	*bytes = 1;
	while (*bytes > 0)
	{
		if (ft_isline(*holder) == 1)
			break ;
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
		{
			*holder = NULL;
			return ;
		}
		*bytes = read(fd, buff, BUFFER_SIZE);
		if (*bytes <= 0)
		{
			free(buff);
			break ;
		}
		*(buff + *bytes) = '\0';
		if (*holder == NULL)
			*holder = buff;
		else
			*holder = ft_strjoin(*holder, buff);
	}
}

static size_t	ft_get_line_len(char *holder)
{
	size_t	len;

	len = 0;
	while (*(holder + len))
	{
		if (*(holder + len) == '\n')
			return (len + 1);
		len++;
	}
	return (len);
}

static void	ft_trim(char **line, char **holder)
{
	size_t	len;
	char	*temp;

	len = ft_get_line_len(*holder);
	// *line = (char *)malloc(sizeof(char) * (len + 1));
	// if (*line == NULL)
	// 	return ;
	*line = ft_substr(*holder, 0, len);
	temp = ft_substr(*holder, len, ft_strlen(*holder));
	free (*holder);
	*holder = temp;
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
	static char	*holder[FD_LIMIT];
	char		*line;
	int			bytes;

	if (fd == -1 || fd > FD_LIMIT || BUFFER_SIZE < 1)
		return (NULL);
	ft_read_buffer(fd, &holder[fd], &bytes);
	if (holder[fd] == NULL || *holder[fd] == '\0')
		return (NULL);
	line = NULL;
	ft_trim(&line, &holder[fd]);
	// if (line == NULL)
	// 	free(holder[fd]);
	return (line);
}

//--------
// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd1;
// 	char	*line;
// 	int		i;

// 	fd1 = open("test1.txt", O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	i = 0;
// 	while (i < 16)
// 	{
// 		line = get_next_line(fd1);
// 		printf("%d: %s\n", i + 1, line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
//--------