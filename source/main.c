/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:23:33 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include "../include/parser.h"
#include "../include/redir.h"
#include "../include/executor.h"

int	g_exit_code;

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

t_lists	*init_list(char **envp)
{
	t_lists			*list;
	t_env_list		*envl;
	t_redir_list	*redirl;
	t_heredoc_list	*heredocl;

	envl = NULL;
	redirl = NULL;
	heredocl = NULL;
	parse_env(&envl, envp);
	list = (t_lists *)malloc(sizeof(t_lists));
	list->envl = envl;
	list->redirl = redirl;
	list->heredocl = heredocl;
	return (list);
}

void	minishell(char **envp)
{
	char			*line;
	t_lists			*list;

	list = init_list(envp);
	while (TRUE)
	{
		line = readline(SHELL_NAME"$ ");
		if (line && ft_strlen(line) > 0)
			line_processing(line, list);
		else if (line == NULL)
		{
			printf("\033[1A\033[5Cexit\n");
			break ;
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term);
	set_term();
	set_signal(HAN, HAN);
	minishell(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
