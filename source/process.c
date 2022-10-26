/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:21:06 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:07 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executor.h"

int	parsing(t_token **toks, t_tree **root, char *line)
{
	if (!scanner(toks, line))
		return (FALSE);
	*toks = get_last_token(*toks);
	*root = get_new_node(LIST, 0, *toks, NULL);
	if (!parser(*root, TRUE))
		return (FALSE);
	return (TRUE);
}

void	roop_convert_toks(t_tree *root, t_lists *list, char **ret)
{
	int		i;

	i = 0;
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
			set_redir(&(list->redirl), new_redir(root->toks->text, \
			root->toks->next->text));
			root->toks = root->toks->next->next;
			continue ;
		}
		ret[i] = root->toks->text;
		root->toks = root->toks->next;
		i++;
	}
	ret[i] = NULL;
}

void	root_free(t_tree *root)
{
	t_token *tmp;

	if (root == NULL)
		return ;
	root_free(root->left);
	root_free(root->right);	
	while (root->toks)
	{
		tmp = root->toks;
		root->toks = root->toks->next;
		free(tmp);
	}
	free(root);
}

char	**convert_toks(t_tree *root, t_lists *list)
{
	char	**ret;
	t_token	*origin;

	origin = root->toks;
	expand(root, list->envl);
	ret = (char **)malloc(sizeof(char *) * (get_toks_length(root->toks) + 1));
	if (!ret)
	{
		ft_putendl_fd("malloc error!", STDERR_FILENO);
		return (NULL);
	}
	roop_convert_toks(root, list, ret);
	root->toks = origin;
	return (ret);
}

void	processing(t_tree *root, t_lists *list, int *prev_fd, int pipe_fd[2])
{
	if (root == NULL)
		return ;
	processing(root->left, list, prev_fd, pipe_fd);
	if (root->type == CTLOP && ((!ft_strcmp(root->toks->text, "&&") \
		&& g_exit_code != EXIT_SUCCESS) || (!ft_strcmp(root->toks->text, "||") \
		&& g_exit_code == EXIT_SUCCESS)))
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
			execute_command(root, convert_toks(root, list), list, -1);
	}
	processing(root->right, list, prev_fd, pipe_fd);
}

void	line_processing(char *line, t_lists *list)
{
	t_token	*toks;
	t_tree	*root;
	int		prev_fd;
	int		pipe_fd[2];

	toks = NULL;
	if (!parsing(&toks, &root, line))
	{
		g_exit_code = 258;
		write(STDERR_FILENO, "syntax err\n", 11);
		return ;
	}
	if (!check_syntax(root, TRUE))
	{
		g_exit_code = 258;
		write(STDERR_FILENO, "syntax err\n", 11);
		return ;
	}
	prev_fd = -1;
	processing(root, list, &prev_fd, pipe_fd);
	root_free(root);
	free_redirl(&list->redirl);
	free_heredocl(&list->heredocl);
	add_history(line);
}
