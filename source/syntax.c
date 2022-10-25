/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:45:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 20:49:31 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

static int	check_left_node(t_tree *root)
{
	const int	type = root->type;

	if (type == CTLOP)
	{
		if (root->left == NULL)
			return (FALSE);
	}
	else if (type == PIPE)
	{
		if (root->left == NULL)
			return (FALSE);
		if (root->left->type == CTLOP || root->left->type == PIPE)
			return (FALSE);
	}
	else if (type == CMD || type == SUBSH)
	{
		if (root->left != NULL)
			return (FALSE);
	}
	return (TRUE);
}

static int	check_right_node(t_tree *root)
{
	const int	type = root->type;

	if (type == CTLOP)
	{
		if (root->right == NULL)
			return (FALSE);
		if (root->right->type == CTLOP)
			return (FALSE);
	}
	else if (type == PIPE)
	{
		if (root->right == NULL)
			return (FALSE);
		if (root->right->type == CTLOP)
			return (FALSE);
	}
	else if (type == CMD || type == SUBSH)
	{
		if (root->right != NULL)
			return (FALSE);
	}
	return (TRUE);
}

int	is_redir(t_token *toks)
{
	return (toks && toks->type == OP && \
			(!ft_strcmp(toks->text, ">") || \
			!ft_strcmp(toks->text, "<") || \
			!ft_strcmp(toks->text, ">>") || \
			!ft_strcmp(toks->text, "<<")));
}

int	match_redir(t_token **toks)
{
	while (*toks)
	{
		if (is_redir(*toks))
		{
			if (!(*toks)->next || (*toks)->next->type != WORD)
				return (FALSE);
		}
		else
			break ;
		*toks = (*toks)->next->next;
	}
	return (TRUE);
}

int	check_node(t_tree *root)
{
	t_token		*toks;
	const int	type = root->type;

	toks = root->toks;
	if (type == CTLOP || type == PIPE)
	{
		if (toks->next || toks->prev)
			return (FALSE);
	}
	else if (type == SUBSH)
	{
		if (!(toks->type == OP && !ft_strcmp(toks->text, "(")))
			return (FALSE);
		while (!(toks->type == OP && !ft_strcmp(toks->text, ")")))
			toks = toks->next;
		if (!match_redir(&(toks->next)))
			return (FALSE);
	}
	else if (type == CMD)
	{
		while (toks)
		{
			if (toks->type == WORD)
			{
				while (toks && toks->type == WORD)
					toks = toks->next;
			}
			if (is_redir(toks))
			{
				if (!match_redir(&toks))
					return (FALSE);
			}
			if (toks)
				toks = toks->next;
		}
	}
	return (TRUE);
}

int	check_syntax(t_tree *root, int ret)
{
	if (!root)
		return (TRUE);
	if (!ret)
		return (FALSE);
	if (!check_left_node(root))
		return (FALSE);
	if (!check_right_node(root))
		return (FALSE);
	if (!check_node(root))
		return (FALSE);
	check_syntax(root->left, ret);
	check_syntax(root->right, ret);
	return (ret);
}
