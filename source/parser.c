/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 17:43:54 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

static int	is_line_op(char *str)
{
	return (!(ft_strcmp(str, "&&") && ft_strcmp(str, "||")));
}

static int	is_paren(char *str)
{
	return (!(ft_strcmp(str, "(") && ft_strcmp(str, ")")));
}

static void	parse_list_loop(t_token **toks, t_tree *root, t_token **tmp, int *success)
{
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN) \
				&& is_line_op((*toks)->text))
		{
			root->flag |= FOUND;
			*success = SUCCESS;
			break ;
		}
		else if ((*toks)->type == OP && is_paren((*toks)->text))
			root->flag ^= PAREN;
		if ((*toks)->prev == NULL)
			*tmp = *toks;
		*toks = (*toks)->prev;
	}
}

int	parse_list(t_tree *root)
{
	int		success;
	t_token	*toks;
	t_token	*tmp;

	toks = root->toks;
	success = 0;
	parse_list_loop(&toks, root, &tmp, &success);
	if (root->flag & PAREN)
		return (FALSE);
	if (!success)
	{
		toks = tmp;
		root->type = PIPELINE;
	}
	root->toks = toks;
	return (TRUE);
}

int	parse_pipeline(t_tree *root)
{
	int		success;
	t_token	*toks;
	t_token	*origin;

	success = 0;
	toks = root->toks;
	origin = toks;
	while (toks)
	{
		if (toks->type == OP && !(root->flag & PAREN) && \
				!ft_strcmp(toks->text, "|"))
		{
			root->flag |= FOUND;
			root->toks = toks;
			success = 1;
			break ;
		}
		else if (toks->type == OP && \
				(!ft_strcmp(toks->text, "(") || \
				!ft_strcmp(toks->text, ")")))
			(root->flag) ^= PAREN;
		toks = toks->next;
	}
	if (root->flag & PAREN)
		return (FALSE);
	if (!success)
	{
		toks = origin;
		root->type = CMD;
	}
	return (TRUE);
}

int	parse_cmd(t_tree *root)
{
	int		subsh;
	t_token	*origin;
	t_token	*toks;

	toks = root->toks;
	origin = toks;
	subsh = FALSE;
	while (toks)
	{
		if (toks->type == OP && \
			(!ft_strcmp(toks->text, "(") || \
			!ft_strcmp(toks->text, ")")))
		{
			(root->flag) ^= PAREN;
			subsh = TRUE;
		}
		toks = toks->next;
	}
	if (root->flag & PAREN)
		return (FALSE);
	else if (subsh == TRUE)
		root->type = SUBSH;
	toks = origin;
	return (TRUE);
}

int	parser(t_tree *root, int ret)
{
	t_tree	*left;
	t_tree	*right;

	if (root == NULL)
		return (TRUE);
	if (ret == FALSE)
		return (FALSE);
	if (root->type == LIST || root->type == SUBSH)
		if (!parse_list(root))
			return (FALSE);
	if (root->type == PIPELINE)
		if (!parse_pipeline(root))
			return (FALSE);
	if (root->type == CMD)
		if (!parse_cmd(root))
			return (FALSE);
	left = make_left_node(root);
	right = make_right_node(root);
	make_root_node(&root);
	root->left = left;
	root->right = right;
	parser(root->right, ret);
	parser(root->left, ret);
	return (ret);
}
