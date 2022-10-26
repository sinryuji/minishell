/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:39:04 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 15:51:18 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

void	flush_pattern(t_list **pattern, t_buf *buf)
{
	if (buf->size)
	{
		ft_lstadd_back(pattern, ft_lstnew(ft_strndup(buf->word, buf->size)));
		free(buf->word);
		init_buf(buf);
	}
}

void	filter_pattern(t_list **pattern)
{
	int		flag;
	t_list	*origin;

	flag = 0;
	origin = *pattern;
	while (*pattern)
	{
		if (!ft_strcmp((*pattern)->content, "*"))
		{
			flag = 1;
			break ;
		}
		*pattern = (*pattern)->next;
	}
	if (!flag)
	{
		ft_lstclear(&origin, free);
		*pattern = NULL;
	}
	else
		*pattern = origin;
}

int	match_pattern_compare(char **str, t_list *pattern, int flag, int len)
{
	char	*tmp;

	if (flag)
	{
		*str = ft_strnstr(*str, pattern->content, ft_strlen(*str));
		if (*str == NULL)
			return (0);
		while (1)
		{
			*str += len;
			tmp = ft_strnstr(*str, pattern->content, ft_strlen(*str));
			if (tmp == NULL)
				break ;
			*str = tmp;
		}
	}
	else
	{
		if (ft_strncmp(*str, pattern->content, len))
			return (0);
	}
	return (1);
}
