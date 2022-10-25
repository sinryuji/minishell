/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:23:25 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 20:32:53 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/redir.h"

static int	read_tmp_file(t_heredoc *heredoc, int tmp)
{
	int	fd;

	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(TMP_FILE);
	if (heredoc->next != NULL)
		dup2(tmp, STDIN_FILENO);
	return (SUCCESS);
}

static int	heredoc_processing(t_heredoc *heredoc, int tmp)
{
	int		fd;
	char	*line;

	if (heredoc == NULL || heredoc->eof == NULL)
		return (FAILURE);
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (FAILURE);
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(line, heredoc->eof))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	if (read_tmp_file(heredoc, tmp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	heredoc(t_heredoc_list *heredocl)
{
	t_heredoc	*heredoc;

	if (heredocl == NULL)
		return (SUCCESS);
	heredoc = heredocl->head;
	if (heredoc == NULL)
		return (SUCCESS);
	while (heredoc)
	{
		if (heredoc_processing(heredoc, heredocl->tmp) == FAILURE)
		{
			ft_puterr("heredoc error!\n");
			g_exit_code = EXIT_FAILURE;
			return (FAILURE);
		}
		heredoc = heredoc->next;
	}
	return (SUCCESS);
}

int	redir_open(char *redir, char *file)
{
	int	fd;

	if (!ft_strcmp("<", redir))
		fd = open(file, O_RDONLY);
	else if (!ft_strcmp(">", redir))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}

int	redir(t_redir_list *redirl)
{
	t_redir	*redir;
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
