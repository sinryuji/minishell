/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/09 20:49:27 by hyeongki         ###   ########.fr       */
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

char	*get_command(char **paths, char *cmd)
{
	if (!paths || !cmd)
		return (NULL);
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
		{
//			execve();
		}

	}
	waitpid(pid, &status, 0);
	return (status);
}

int	get_fork()
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
