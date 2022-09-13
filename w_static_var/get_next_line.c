/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:38:02 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/13 17:30:34 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

						#include <stdio.h> // DEBUG
#include "get_next_line.h"
#define FD_LIMIT 1024
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#if (BUFFER_SIZE > 1000)
# undef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

static void	ft_read_buffer(int fd, char **buff)
{
	char	*tempbuff;
	int		bytes;

	if (*buff == NULL)
	{
		*buff = malloc(1);
		if (*buff == NULL)
			return ;
		**buff ='\0';
	}
	while (1)
	{
		tempbuff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (tempbuff == NULL)
		{
			*buff = NULL;
			return ;
		}
		bytes = read(fd, tempbuff, BUFFER_SIZE);
		*(tempbuff + bytes) = '\0';
		if (bytes != 0)
			*buff = ft_strjoin(*buff, tempbuff);
		free(tempbuff);
		if (ft_isline(*buff) == 1 || bytes == 0)
			break ;
	}
}

static size_t	ft_get_line_len(char *buff)
{
	size_t	len;

	len = 0;
	while (*(buff + len))
	{
		len++;
		if (*(buff + len) == '\n')
			break ;
	}
	return (len);
}

static void	ft_trim(char **line, char **buff)
{
	size_t	len;
	char	*temp;

	len = ft_get_line_len(*buff) + 1;
	*line = (char *)malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
	*line = ft_substr(*buff, 0, len);
	temp = ft_substr(*buff, len, ft_strlen(*buff) - len);
	//free (*buff);
	*buff = temp;
	// free (temp); 
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
	char		*line;
	static char	*buff;

	if (fd == -1 || fd > FD_LIMIT || BUFFER_SIZE < 1)
		return (NULL);
	ft_read_buffer(fd, &buff);
	if (buff == NULL)
		return (NULL);
	line = NULL;
	// printf("buff (before trim): %s\n\n", buff);
	ft_trim(&line, &buff);
	// printf("line: %s\n", line);
	// printf("buff (after trim): %s\n", buff);
	// printf("-----------\n\n");



	// if (len > 0)
	// {
	// 	line = extract_line(buff, len);
	// 	buff = trim_buff(buff, len);
	// }
	return (line);
}

// //--------
// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd1;
// 	char	*line;
// 	int		i;

// 	fd1 = open("test0.txt", O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	i = 0;
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd1);
// 		printf("%s", line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
// //--------