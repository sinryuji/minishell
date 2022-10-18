/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:49 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/17 19:00:28 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	excute_pipe(t_tree *node, t_env_list *envl)
{
	int		pipe_fd[2];
	pid_t	pid;

	// 두번쨰 놈한테 파이프를 넘겨줘야하는구나! 집에가서 하자!
	if (pipe(pipe_fd) == -1)
		ft_perror_exit("pipe error\n");
	// 자식은 dup 따고 execute
	// 부모는 wait_child() 호출
	pid = ft_fork();
	if (pid == 0)
	{
		if (who_am_i(node) == LEFT)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		else
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
			execute_command(convert_toks(node), envl, pipe_fd);
	}
	else
		wait_child();
//	if (get_sibilng_node(node)->type != PIPE)
//	{
//
//	}
//	else 
//	{
//
//	}
}
