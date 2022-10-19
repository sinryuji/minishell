/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/18 22:04:52 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include "../include/parser.h"
#include <stdlib.h>

int	g_exit_code;

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	get_fork(void)
{
	return (FALSE);
}

char	**convert_toks(t_tree *root)
{
	char	**ret;
	t_token	*origin;
	int		cnt;
	int		i;

	origin = root->toks;
	cnt = 0;
	i = 0;
	while (root->toks)
	{
		cnt++;
		root->toks = root->toks->next;
	}
	root->toks = origin;
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	while (root->toks)
	{
		ret[i] = root->toks->text;
		i++;
		root->toks = root->toks->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	processing(t_tree *root, t_env_list *envl)
{
	static int	pipe_fd[2];

	if (root == NULL)
		return ;
	processing(root->left, envl);
	if (root->type == CTLOP && (!ft_strcmp(root->toks->text, "&&") && g_exit_code != EXIT_SUCCESS) || (!ft_strcmp(root->toks->text, "||") && g_exit_code == EXIT_SUCCESS))
		return ;
	if (root->type == CMD)
	{
		if (root->parent != NULL && root->parent->type == PIPE)
		{
			if (who_am_i(root) == LEFT)
				if (pipe(pipe_fd) == -1)
					ft_perror_exit("pipe error\n");
			excute_pipe(root, envl, pipe_fd);
		}
		else
			execute_command(convert_toks(root), envl, -1);
	}
	processing(root->right, envl);
}

void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("type : %d, text : %s\n", toks->type, toks->text);
		toks = toks->next;
	}
}

void	print_tree(t_tree *root)
{
	t_token	*origin;

	if (root == NULL)
		return ;
	print_tree(root->left);
	origin = root->toks;
	while (root->toks)
	{
		printf("%s ", root->toks->text);
		root->toks = root->toks->next;
	}
	root->toks = origin;
	printf("\n");
	print_tree(root->right);
}

void	syntax_check(t_tree *root)
{
	if (root == NULL)
		return ;
	// 전위 순회하며 syntax error 잡기
	syntax_check(root->left);
	syntax_check(root->right);
}

void	parsing(t_token **toks, t_tree **root, char *line)
{
	scanner(toks, line);
	print_toks(*toks);
	*toks =  get_last_token(*toks);
	*root = get_new_node(LIST, 0, *toks, NULL);
	parser(*root);
	print_tree(*root);
	//syntax check fnction
}

void	minishell(char **envp)
{
	char			*line;
	t_env_list		*envl;
	t_token			*toks;
	t_tree			*root;

	envl = NULL;
	parse_env(&envl, envp);
	while (TRUE)
	{
		toks = NULL;
		line = readline(SHELL_NAME"$ ");
		if (line && ft_strlen(line) > 0)
		{
			parsing(&toks, &root, line);
			printf("execute=================================================\n");
			processing(root, envl);
			add_history(line);
		}
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
