/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"
#include "../include/as_tree.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <signal.h>

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

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	struct termios	term;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline("fdf$ ");
		if (line)
			printf("%s\n", line);
		else
			break ;
		add_history(line);
	}
	return (0);
}
