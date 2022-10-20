/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:49 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/20 14:52:09 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	first_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)	
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(convert_toks(node, list->redirl), list, pid);
	}
	else
		close(pipe_fd[1]);
}

static void	middle_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(convert_toks(node, list->redirl), list, pid);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	last_pipe(t_tree *node, t_lists *list, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(convert_toks(node, list->redirl), list, pid);
	}
	else
	{
		close(pipe_fd[0]);
		wait_child();
	}
}

void	excute_pipe(t_tree *node, t_lists *list, int pipe_in, int pipe_out)
{
	pid_t	pid;
	int		tmp[2];

	// middle_pipe가 이전에 파놨던 파이프의 wirte로 read하고, 새로 판 파이프의 read로 wirte해야하는구나
	tmp[0] = pipe_in;
	tmp[1] = pipe_out;
	pid = ft_fork();
	if (who_am_i(node) == RIGHT)
		last_pipe(node, list, pid, tmp);
	else if (node->parent->parent != NULL && node->parent->parent->type == PIPE)
		middle_pipe(node, list, pid, tmp);
	else
		first_pipe(node, list, pid, tmp);
}
