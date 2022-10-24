/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:58:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/24 20:07:12 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include "../include/parser.h"
#include "../include/redir.h"
#include "../include/executor.h"
#include "../include/executor.h"

int	g_exit_code;

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	get_toks_length(t_token *toks)
{
	int	ret;

	ret = 0;
	while (toks)
	{
		ret++;
		toks = toks->next;
	}
	return (ret);
}

char	**convert_toks(t_tree *root, t_lists *list)
{
	char	**ret;
	int		len;
	int		i;

	expand(root, list->envl);
	i = 0;
	len = get_toks_length(root->toks);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
	{
		ft_putendl_fd("malloc error!", STDERR_FILENO);
		return (NULL);
	}
	while (root->toks)
	{
		if (!ft_strcmp("<<", root->toks->text))
		{
			set_heredoc(&(list->heredocl), new_heredoc(root->toks->next->text));
			root->toks = root->toks->next->next;
			continue ;
		}
		else if (is_redir(root->toks) == TRUE)
		{
			set_redir(&(list->redirl), new_redir(root->toks->text, root->toks->next->text));
			root->toks = root->toks->next->next;
			continue ;
		}
		ret[i] = root->toks->text;
		i++;
		root->toks = root->toks->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	processing(t_tree *root, t_lists *list, int *prev_fd, int pipe_fd[2])
{
	if (root == NULL)
		return ;
	processing(root->left, list, prev_fd, pipe_fd);
	if (root->type == CTLOP && ((!ft_strcmp(root->toks->text, "&&") && g_exit_code != EXIT_SUCCESS) || (!ft_strcmp(root->toks->text, "||") && g_exit_code == EXIT_SUCCESS)))
		return ;
	if (root->type == CMD || root->type == SUBSH)
	{
		if (root->parent != NULL && root->parent->type == PIPE)
		{
			if (who_am_i(root) == LEFT)
				if (pipe(pipe_fd) == -1)
					ft_perror_exit("pipe error\n");
			excute_pipe(root, list, *prev_fd, pipe_fd);
			*prev_fd = pipe_fd[0];
		}
		else
			execute_command(convert_toks(root, list), list, -1);
	}
	processing(root->right, list, prev_fd, pipe_fd);
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

void	parsing(t_token **toks, t_tree **root, char *line)
{
	scanner(toks, line);
	print_toks(*toks);
	*toks =  get_last_token(*toks);
	*root = get_new_node(LIST, 0, *toks, NULL);
	parser(*root);
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

void	line_processing(char *line, t_lists *list)
{
	t_token *toks;
	t_tree	*root;
	int		prev_fd;
	int		pipe_fd[2];

	toks = NULL;
	parsing(&toks, &root, line);
	print_tree(root);
	check_syntax(root);
	prev_fd = -1;
	processing(root, list, &prev_fd, pipe_fd);
	free_redirl(&list->redirl);
	free_heredocl(&list->heredocl);
	add_history(line);
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
