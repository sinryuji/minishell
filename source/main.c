/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/10 13:48:57 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	dir_check(char *path, char *cmd)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;

	dir_info = opendir(path);
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

int	execute_command(char **argv, t_env_list *envl, int fork_flag, pid_t pid)
{
	int		status;
	char	*cmd;

	cmd = get_command(ft_split(get_env(envl, "PATH")->value, ':'), argv[0]);
	if (cmd == NULL)
	{
		put_error_cmd(argv[0], "command not found");
		if (fork_flag == TRUE)
			exit(CMD_NOTFOUND);
	}
	else
	{
		if (fork_flag == FALSE)
			pid = fork();
		if (pid == 0)
			execve(cmd, argv, reverse_env(envl));
	}
	waitpid(pid, &status, 0);
	free(cmd);
	return (status);
}

int	get_fork(void)
{
	return (FALSE);
}

void	processing(char **argv, t_env_list *envl)
{
	int			fork_flag;
	t_built_in	built_in;
	pid_t		pid;

	built_in = get_built_in(argv[0]);
	fork_flag = get_fork();
	if (fork_flag == TRUE)
		pid = fork();
	if (built_in)
		built_in(get_argc(argv), argv, envl);
	else
		execute_command(argv, envl, fork_flag, pid);
	ft_split_free(argv);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	struct termios	term;
	t_env_list		*envl;

	tcgetattr(STDIN_FILENO, &term);
	set_term();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	envl = NULL;
	parse_env(&envl, envp);
	while (TRUE)
	{
		line = readline(SHELL_NAME"$ ");
		if (line && ft_strlen(line) > 0)
		{
			processing(ft_split(line, ' '), envl);
			add_history(line);
		}
		else if (line == NULL)
		{
			printf("\033[1A\033[5Cexit\n");
			break ;
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
