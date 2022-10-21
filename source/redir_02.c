/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:55:13 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/21 16:10:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/redir.h"

//int	is_redirection(char *text)
//{
//	if (!ft_strcmp("<", text) || !ft_strcmp(">", text) || !ft_strcmp(">>", text) || !ft_strcmp("<<", text))
//		return (TRUE);
//	return (FALSE);
//}

t_redir	*new_redir(char *redir, char *file)
{
	t_redir	*new;

	if (!redir || !file)
		return (NULL);
	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->redir = ft_strdup(redir);
	new->file = ft_strdup(file);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	set_redir(t_redir_list **redirl, t_redir *new)
{
	if (!new)
		return (FAILURE);
	if (!*redirl)
	{
		*redirl = (t_redir_list *)malloc(sizeof(t_redir_list));
		if (!*redirl)
			return (FAILURE);
		(*redirl)->head = new;
		(*redirl)->tail = new;
		(*redirl)->tmp[0] = dup(STDIN_FILENO);
		(*redirl)->tmp[1] = dup(STDOUT_FILENO);
	}
	else
	{
		(*redirl)->tail->next = new;
		new->prev = (*redirl)->tail;
		(*redirl)->tail = new;
	}
	return (SUCCESS);
}

void	free_redir(t_redir *redir)
{
	free(redir->redir);
	redir->redir = NULL;
	free(redir->file);
	redir->file = NULL;
	free(redir);
	redir = NULL;
}

void	free_redirl(t_redir_list **redirl)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!*redirl)
		return ;
	redir = (*redirl)->head;
	if (!redir)
		return ;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp)
			free_redir(tmp);
	}
	if (*redirl)
		free(*redirl);
	*redirl = NULL;
}
