/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:49:38 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 20:09:00 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/executor.h"

void	execute_subshell(t_token *toks, t_lists *list, pid_t pid)
{
	t_tree	*new;
	int		prev_fd;
	int		pipe_fd[2];

	if (pid == -1)
		pid = ft_fork();
	if (pid == 0)
	{
		remove_parenthesis(&toks);
		toks = get_last_token(toks);
		new = get_new_node(LIST, 0, toks, NULL);
		if (!parser(new, TRUE))
			set_exit_code(258);
		free_redirl(&list->redirl);
		free_heredocl(&list->heredocl);
		if (!check_syntax(new, TRUE))
			set_exit_code(258);
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
			put_error_cmd_exit(argv[0], "No such file or directory", \
					CMD_NOT_FOUND);
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

int	execute_prework(t_lists *list, char **argv, pid_t pid)
{
	if (heredoc(list->heredocl) == FAILURE || redir(list->redirl) == FAILURE)
	{
		if (pid == 0)
			exit(g_exit_code);
		else
			return (FALSE);
	}
	if (argv == NULL || argv[0] == NULL)
	{
		redup_descriptor(list);
		return (FALSE);
	}
	return (SUCCESS);
}

void	execute_command(t_tree *root, char **argv, t_lists *list, pid_t pid)
{
	t_built_in	built_in;

	if (execute_prework(list, argv, pid) == FALSE)
		return ;
	if (root->type == SUBSH)
	{
		execute_subshell(root->toks, list, pid);
		redup_descriptor(list);
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
	redup_descriptor(list);
	ft_split_free(argv);
}
