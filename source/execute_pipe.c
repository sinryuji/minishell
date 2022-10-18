/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:49 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/18 15:35:09 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	left_node_processing(t_tree *node, t_env_list *envl, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)	
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_command(convert_toks(node), envl, pid);
	}
	else
		wait_child();
}

void	right_node_processing(t_tree *node, t_env_list *envl, pid_t pid, int pipe_fd[2])
{
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
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

	// 두번쨰 놈한테 파이프를 넘겨줘야하는구나! 집에가서 하자!
	// 자식은 dup 따고 execute
	// 부모는 wait_child() 호출
	pid = ft_fork();
	if (who_am_i(node) == LEFT)
		left_node_processing(node, envl, pid, pipe_fd);
	else
		right_node_processing(node, envl, pid, pipe_fd);
//	if (get_sibilng_node(node)->type != PIPE)
//	{
//
//	}
//	else 
//	{
//
//	}
}
