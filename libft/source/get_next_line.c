/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:36:51 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/09 20:03:40 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <unistd.h>

#define BUFFER_SIZE 42

static char	*get_line(char **save)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	if (!**save)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	while (*(*save + i) && *(*save + i) != '\n')
		i++;
	ret = ft_substr(*save, 0, i + 1);
	tmp = ft_substr(*save, i + 1, ft_strlen(*save) - ft_strlen(ret));
	free(*save);
	*save = tmp;
	return (ret);
}

static char	*read_line(int fd, char *save, char *buf)
{
	ssize_t	read_byte;
	char	*tmp;

	read_byte = 1;
	while (!(ft_strchr(save, '\n')) && read_byte != 0)
	{	
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_byte] = 0;
		if (!save)
			tmp = ft_strdup(buf);
		else
			tmp = ft_strjoin(save, buf);
		free(save);
		save = tmp;
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save = read_line(fd, save, buf);
	if (!save)
		return (NULL);
	return (get_line(&save));
}
