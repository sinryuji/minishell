/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:49:38 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/18 14:11:19 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	dir_check(char *path, char *cmd)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;

	dir_info = opendir(path);
	if (dir_info == NULL)
		return (FALSE);
	while (TRUE)
	{
		dir_entry = readdir(dir_info);
		if (dir_entry == NULL)
			break ;
		if (ft_strcmp(dir_entry->d_name, cmd) == 0)
		{
			closedir(dir_info);
			return (TRUE);
		}
	}
	closedir(dir_info);
	return (FALSE);
}

char	*get_command(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
	{
		if (dir_check(paths[i], cmd) == TRUE)
		{
			tmp = ft_strjoin("/", cmd);
			ret = ft_strjoin(paths[i], tmp);
			free(tmp);
			ft_split_free(paths);
			return (ret);
		}
		i++;
	}
	ft_split_free(paths);
	return (NULL);
}

void	wait_child(void)
{
	int		status;
	int		sig;
	int		i;

	i = 0;
	set_signal(IGN, IGN);
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT && i == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (sig == SIGQUIT && i == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_code = sig + 128;
			i++;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
	set_signal(HAN, HAN);
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

void	execute_command(char **argv, t_env_list *envl, pid_t pid)
{
//	int			fork_flag;
	t_built_in	built_in;

	built_in = get_built_in(argv[0]);
//	fork_flag = get_fork();
//	pid = -1;
//	if (pipe_fd != NULL)
//		pid = ft_fork();
	if (built_in)
	{
		g_exit_code = built_in(get_argc(argv), argv, envl);
		if (pid == 0)
			exit(g_exit_code);
	}
	else
		execve_command(argv, envl, pid);
	ft_split_free(argv);
}
