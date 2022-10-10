/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:49:38 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 21:04:06 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
}

void	execute_command(char **argv, t_env_list *envl, int fork_flag, pid_t pid)
{
	char	*cmd;

	if (fork_flag == FALSE)
		pid = fork();
	if (pid == 0)
	{
		set_signal(DFL, DFL);
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
		set_signal(IGN, IGN);
	wait_child();
}
