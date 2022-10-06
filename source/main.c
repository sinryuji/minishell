/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/06 20:53:30 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
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

void	child_process(int pipe_fd[], char **argv, t_env_list *envl)
{
	int	ret;

	ret = built_in(argv[0], argv + 1, envl);
	if (ret == -1)
	{

	}
	else
		exit(ret);
}

void	processing(char **argv, t_env_list *envl)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!*argv)
		return ;
	if (pipe(pipe_fd) == -1)
		ft_perror_exit("pipe error\n");
	pid = fork();
	if (pid == 0)
		child_process(pipe_fd, argv, envl);
	waitpid(pid, &status, 0);
	printf("%d\n", status);
	ft_split_free(argv);
	if (status < 0)
		exit(status);
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
	while (1)
	{
		line = readline(SHELL_NAME"$ ");
		if (line)
			processing(ft_split(line, ' '), envl);
		else
		{
			printf("\033[1A\033[5Cexit\n");
			break ;
		}
		add_history(line);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
