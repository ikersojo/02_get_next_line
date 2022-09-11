/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:38:41 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/07 21:59:36 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*ft_strjoin(char *line, char *buff);
int		ft_isline(char *str);
size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
char	*read_buffer(size_t size, int fd);
char	*get_line(size_t size, int fd);
#endif