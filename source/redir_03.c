/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:08:52 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/20 20:59:04 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/redir.h"

t_heredoc	*new_heredoc(char *eof)
{
	t_heredoc	*new;

	if (!eof)
		return (NULL);
	new = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->eof = ft_strdup(eof);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	set_heredoc(t_heredoc_list **heredocl, t_heredoc *new)
{
	if (!new)
		return (FAILURE);
	if (!*heredocl)
	{
		*heredocl = (t_heredoc_list *)malloc(sizeof(t_heredoc_list));
		if (!*heredocl)
			return (FAILURE);
		(*heredocl)->head = new;
		(*heredocl)->tail = new;
		(*heredocl)->tmp = dup(STDIN_FILENO);
	}
	else
	{
		(*heredocl)->tail->next = new;
		new->prev = (*heredocl)->tail;
		(*heredocl)->tail = new;
	}
	return (SUCCESS);
}

void	free_heredoc(t_heredoc *heredoc)
{
	free(heredoc->eof);
	heredoc->eof = NULL;
	free(heredoc);
	heredoc = NULL;
}

void	free_heredocl(t_heredoc_list **heredocl)
{
	t_heredoc	*heredoc;
	t_heredoc	*tmp;

	if (!*heredocl)
		return ;
	heredoc = (*heredocl)->head;
	if (!heredoc)
		return ;
	while (heredoc)
	{
		tmp = heredoc;
		heredoc = heredoc->next;
		if (tmp)
			free_heredoc(tmp);
	}
	if (*heredocl)
		free(*heredocl);
	*heredocl = NULL;
}
