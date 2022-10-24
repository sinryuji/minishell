/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:49 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/24 22:23:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	first_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)	
	{
		dup2(pipe_fd[2], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd[2]);
		execute_command(node, convert_toks(node, list), list, pid);
	}
	else
		close(pipe_fd[2]);
}

static void	middle_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd[2], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd[2]);
		execute_command(node, convert_toks(node, list), list, pid);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[2]);
	}
}

static void	last_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[3])
{
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd[2]);
		execute_command(node, convert_toks(node, list), list, pid);
	}
	else
	{
		close(pipe_fd[0]);
		wait_child();
	}
}

void	excute_pipe(t_tree *node, t_lists *list, int pipe_in, int pipe_fd[2])
{
	pid_t	pid;
	int		tmp[3];

	tmp[0] = pipe_in;
	tmp[1] = pipe_fd[0];
	tmp[2] = pipe_fd[1];
	pid = ft_fork();
	if (who_am_i(node) == RIGHT)
		last_pipe(node, list, pid, tmp);
	else if (node->parent->parent != NULL && node->parent->parent->type == PIPE)
		middle_pipe(node, list, pid, tmp);
	else
		first_pipe(node, list, pid, tmp);
}
