/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/17 17:29:35 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include "../include/parser.h"
#include "../include/executor.h"

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
		g_exit_code = built_in(get_argc(argv), argv, envl);
	else
		execute_command(argv, envl, fork_flag, pid);
	set_signal(HAN, HAN);
	ft_split_free(argv);
}

void	print_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	while (root->toks)
	{
		printf("%s ", root->toks->text);
		root->toks = root->toks->next;
	}
	printf("\n");
	print_tree(root->left);
	print_tree(root->right);
}

void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("type : %d, text : %s\n", toks->type, toks->text);
		toks = toks->next;
	}
}

void	parsing(t_token **toks, t_tree **root, char *line)
{
	scanner(toks, line);
	print_toks(*toks);
	*toks =  get_last_token(*toks);
	*root = get_new_node(LIST, 0, *toks);
	parser(*root);
	print_tree(*root);
	printf("\n");
	//syntax check fnction
}

void	tree_traverse(t_tree *root, t_env_list *envl)
{
	(void)root;
	(void)envl;
//	processing(, envl);
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
			check_syntax(root);
			//tree_travese()
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
