/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:23:25 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/20 17:11:52 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/redir.h"

int	is_redir(char *text)
{
	if (!ft_strcmp("<", text) || !ft_strcmp(">", text) || !ft_strcmp(">>", text))
		return (TRUE);
	return (FALSE);
}

int	redir_open(char *redir, char *file)
{
	int	fd;

	if (!ft_strcmp("<", redir))
		fd = open(file, O_RDONLY);
	else if (!ft_strcmp(">", redir))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!ft_strcmp(">>", redir))
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}

int	redir(t_redir_list *redirl, pid_t pid)
{
	t_redir *redir;
	int		fd;

	if (redirl == NULL)
		return (SUCCESS);
	redir = redirl->head;
	if (redir == NULL)
		return (SUCCESS);
	while (redir)
	{
		fd = redir_open(redir->redir, redir->file);
		if (fd == -1)
		{
			put_error_cmd(redir->file, strerror(errno));
			g_exit_code = EXIT_FAILURE;
			return (FAILURE);
		}
		if (!ft_strcmp("<", redir->redir))
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (SUCCESS);
}
