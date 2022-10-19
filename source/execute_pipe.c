/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:49 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/18 22:30:54 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	first_pipe(t_tree *node, t_env_list *envl, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)	
	{
		printf("first pipe!\n");
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_command(convert_toks(node), envl, pid);
	}
}

void	middle_pipe(t_tree *node, t_env_list *envl, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		printf("middle pipe!\n");
//		dup2(pipe_fd[0], STDIN_FILENO);
//		dup2(pipe_fd[1], STDOUT_FILENO);
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execute_command(convert_toks(node), envl, pid);
	}
}

void	last_pipe(t_tree *node, t_env_list *envl, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		printf("last pipe!\n");
//		close(pipe_fd[1]);
//		dup2(pipe_fd[0], STDIN_FILENO);
//		close(pipe_fd[0]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(convert_toks(node), envl, pid);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait_child();
	}
}

void	excute_pipe(t_tree *node, t_env_list *envl, int pipe_fd[2])
{
	pid_t	pid;

	// middle_pipe가 이전에 파놨던 파이프의 wirte로 read하고, 새로 판 파이프의 read로 wirte해야하는구나
	pid = ft_fork();
	if (who_am_i(node) == RIGHT)
		last_pipe(node, envl, pid, pipe_fd);
	else if (node->parent->parent != NULL && node->parent->parent->type == PIPE)
		middle_pipe(node, envl, pid, pipe_fd);
	else
		first_pipe(node, envl, pid, pipe_fd);
//	if (get_sibilng_node(node)->type != PIPE)
//	{
//
//	}
//	else 
//	{
//
//	}
}
