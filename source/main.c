/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/06 15:08:52 by hyeongki         ###   ########.fr       */
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

void	processing(char *line, t_env_list *envl)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
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
	ft_export(0, NULL, envl);
	printf("\n\n\n");
	char	*str[2];
	str[0] = "PATH";
	str[1] = "asdf";
	ft_unset(1, str, envl);
	ft_export(0, NULL, envl);
	while (1)
	{
		line = readline(SHELL_NAME"$ ");
		if (line)
			processing(line, envl);
		else
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
