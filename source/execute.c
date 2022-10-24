/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:49:38 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/23 21:20:31 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

void	execute_subshell(char **envp)
{
	pid_t pid;

	printf("subshell?\n");
	pid = ft_fork();
	if (pid == 0)
		minishell(envp);
	else
		wait_child();
}

void	execve_command(char **argv, t_env_list *envl, pid_t pid)
{
	char	*cmd;

	if (pid == -1)
		pid = ft_fork();
	if (pid == 0)
	{
		if (*argv[0] == '.')
		{
			if (execve(argv[0], argv, reverse_env(envl)) == -1)
				put_error_cmd_exit(argv[0], "command not found", CMD_NOT_FOUND);
		}
		else
		{
			cmd = get_command(ft_split(get_env(envl, "PATH")->value, ':'), \
					argv[0]);
			if (cmd == NULL)
				put_error_cmd_exit(argv[0], "command not found", CMD_NOT_FOUND);
			else
				execve(cmd, argv, reverse_env(envl));
		}
	}
	else
		wait_child();
}

void	execute_command(char **argv, t_lists *list, pid_t pid)
{
	t_built_in	built_in;

	if (heredoc(list->heredocl) == FAILURE)
	{
		if (pid == 0)
			exit(g_exit_code);
		else
			return ;
	}
	if (redir(list->redirl) == FAILURE)
	{
		if (pid == 0)
			exit(g_exit_code);
		else
			return ;
	}
	if (argv == NULL || argv[0] == NULL)
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
	built_in = get_built_in(argv[0]);
	if (built_in)
	{
		g_exit_code = built_in(get_argc(argv), argv, list->envl);
		if (pid == 0)
			exit(g_exit_code);
	}
	else
		execve_command(argv, list->envl, pid);
	if (list->redirl)
	{
		dup2(list->redirl->tmp[0], STDIN_FILENO);
		dup2(list->redirl->tmp[1], STDOUT_FILENO);
	}
	if (list->heredocl)
		dup2(list->heredocl->tmp, STDIN_FILENO);
	ft_split_free(argv);
}
