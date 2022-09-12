/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:38:02 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/12 23:20:47 by isojo-go         ###   ########.fr       */
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


// size_t	ft_get_line_len(char *buff)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*(buff + len))
// 	{
// 		len++;
// 		if (*(buff + len) == '\n')
// 			break ;
// 	}
// 	return (len);
// }

// char	*extract_line(char *buff, size_t len)
// {
// 	size_t	i;
// 	char	*line;

// 	line = (char *)malloc(sizeof(char) * (len + 1));
// 	if (line == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 		*(line + i++) = *buff++;
// 	*(line + i++) = '\0';
// 	return (line);
// }

// char	*trim_buff(char *buff, size_t len)
// {
// 	char	*trimmed;
// 	size_t	i;

// 	trimmed = (char *)malloc(sizeof(char) * (ft_strlen(buff) - len + 1));
// 	if (trimmed == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (len < ft_strlen(buff))
// 		*(trimmed + i++) = *(buff + len++);
// 	*(trimmed + i) = '\0';
// 	return (trimmed);
// }

static char	*read_buffer(int fd, char *buff)
{
	char	*tempbuff;
	int		bytes;

	bytes = 1;
	while (!ft_strchr(buff, '\n') && bytes != 0)
	{
		tempbuff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (tempbuff == NULL)
			return (NULL);
		bytes = read(fd, tempbuff, BUFFER_SIZE);
				printf("   - bytes: %d\n\n", bytes); // DEBUG
		*(tempbuff + bytes) = '\0';
		buff = ft_strjoin(buff, tempbuff);
		printf("   - buff: %s\n\n", buff); // DEBIUG
	}
	return (buff);
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

	len = ft_get_line_len(*buff);
	*line = (char *)malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
	*line = ft_substr(*buff, 0, len);
	temp = ft_substr(*buff, len, ft_strlen(*buff) - len);
	free (*buff);
	*buff = temp;
	free (temp); 
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
	buff = read_buffer(fd, buff);
	if (buff == NULL)
		return (NULL);
	ft_trim(&line, &buff);


	//line = NULL;
	// len = ft_get_line_len(buff);
	// if (len > 0)
	// {
	// 	line = extract_line(buff, len);
	// 	buff = trim_buff(buff, len);
	// }
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
	while (i < 4)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		i++;
	}
	close(fd1);
	return (0);
}

