/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:49:38 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 15:54:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/executor.h"

void	execute_subshell(t_tree *root, t_token *toks, t_lists *list, pid_t pid)
{
	t_tree	*new;
	int		prev_fd;
	int		pipe_fd[2];

	(void)root;
	if (pid == -1)
		pid = ft_fork();
	if (pid == 0)
	{
		remove_parenthesis(&toks);
		toks = get_last_token(toks);
		new = get_new_node(LIST, 0, toks, NULL);
		parser(new);
		free_redirl(&list->redirl);
		free_heredocl(&list->heredocl);
		check_syntax(new);
		expand(new, list->envl);
		prev_fd = -1;
		processing(new, list, &prev_fd, pipe_fd);
		exit(g_exit_code);
	}
	else
		wait_child();
}

void	execve_command(char **argv, t_env_list *envl, pid_t pid)
{
	char	*cmd;
	int		flag;

	flag = TRUE;
	if (pid == -1)
		pid = ft_fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, reverse_env(envl)) == -1)
			flag = FALSE;
		if (get_env(envl, "PATH") == NULL)
			put_error_cmd_exit(argv[0], "No such file or directory", CMD_NOT_FOUND);
		cmd = get_command(ft_split(get_env(envl, "PATH")->value, ':'), \
				argv[0]);
		if (cmd != NULL)
			flag = TRUE;
		if (flag == FALSE)
			put_error_cmd_exit(argv[0], "command not found", CMD_NOT_FOUND);
		else
			execve(cmd, argv, reverse_env(envl));
	}
	else
		wait_child();
}

void	execute_command(t_tree *root, char **argv, t_lists *list, pid_t pid)
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
	if (root->type == SUBSH)
	{
		execute_subshell(root, root->toks, list, pid);
		if (list->redirl)
		{
			dup2(list->redirl->tmp[0], STDIN_FILENO);
			dup2(list->redirl->tmp[1], STDOUT_FILENO);
		}
		if (list->heredocl)
			dup2(list->heredocl->tmp, STDIN_FILENO);
		return ;
	}
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
