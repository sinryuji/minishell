/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:28:27 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 20:59:36 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
		ft_perror_exit("fork error\n");
	if (ret == 0)
		set_signal(DFL, DFL);
	return (ret);
}

int	dir_check(char *path, char *cmd)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;

	dir_info = opendir(path);
	if (dir_info == NULL)
		return (FALSE);
	while (TRUE)
	{
		dir_entry = readdir(dir_info);
		if (dir_entry == NULL)
			break ;
		if (ft_strcmp(dir_entry->d_name, cmd) == 0)
		{
			closedir(dir_info);
			return (TRUE);
		}
	}
	closedir(dir_info);
	return (FALSE);
}

char	*get_command(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
	{
		if (dir_check(paths[i], cmd) == TRUE)
		{
			tmp = ft_strjoin("/", cmd);
			ret = ft_strjoin(paths[i], tmp);
			free(tmp);
			ft_split_free(paths);
			return (ret);
		}
		i++;
	}
	ft_split_free(paths);
	return (NULL);
}

void	remove_parenthesis(t_token **toks)
{
	t_token	*tmp;

	tmp = (*toks)->next;
	tmp->prev = NULL;
	free((*toks)->text);
	free(*toks);
	*toks = tmp;
	while (ft_strcmp((*toks)->text, ")"))
		*toks = (*toks)->next;
	(*toks)->prev->next = NULL;
	free((*toks)->text);
	free(*toks);
	*toks = tmp;
}

void	redup_descriptor(t_lists *list)
{
	if (list->redirl)
	{
		dup2(list->redirl->tmp[0], STDIN_FILENO);
		dup2(list->redirl->tmp[1], STDOUT_FILENO);
	}
	if (list->heredocl)
		dup2(list->heredocl->tmp, STDIN_FILENO);
	return ;
}
