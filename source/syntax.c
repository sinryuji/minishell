/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:45:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/17 18:52:28 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"

static void	check_left_node(t_tree *root)
{
	const int	type = root->type;

	if (type == CTLOP)
	{
		if (root->left == NULL)
			err_exit(ERR_MSG);
	}
	else if (type == PIPE)
	{
		if (root->left == NULL)
			err_exit(ERR_MSG);
		if (root->left->type == CTLOP)
			err_exit(ERR_MSG);
	}
	else if (type == CMD || type == SUBSH)
	{
		if (root->left != NULL)
			err_exit(ERR_MSG);
	}
}

static void	check_right_node(t_tree *root)
{
	const int	type = root->type;

	if (type == CTLOP)
	{
		if (root->right == NULL)
			err_exit(ERR_MSG);
		if (root->right->type == CTLOP)
			err_exit(ERR_MSG);
	}
	else if (type == PIPE)
	{
		if (root->right == NULL)
			err_exit(ERR_MSG);
		if (root->right->type == CTLOP || root->right->type == PIPE)
			err_exit(ERR_MSG);
	}
	else if (type == CMD || type == SUBSH)
	{
		if (root->right != NULL)
			err_exit(ERR_MSG);
	}
}

int	is_redir(t_token *toks)
{
	return ( toks && toks->type == OP && \
			(!ft_strcmp(toks->text, ">") || \
			 !ft_strcmp(toks->text, "<") || \
			 !ft_strcmp(toks->text, ">>") || \
			 !ft_strcmp(toks->text, "<<")));
}

void	match_redir(t_token *toks)
{
	while (toks)
	{
		if (is_redir(toks))
		{
			if (toks->next->type != WORD)
				err_exit(ERR_MSG);
		}
		else
			break ;
		toks = toks->next->next;
	}
}

void	check_node(t_tree *root)
{
	t_token		*toks;
	const int	type = root->type;

	toks = root->toks;
	if (type == CTLOP || type == PIPE)
	{
		if (toks->next || toks->prev)
			err_exit(ERR_MSG);
	}
	else if (type == SUBSH)
	{
		if (!(toks->type == OP && !ft_strcmp(toks->text, "(")))
			err_exit(ERR_MSG);
		while (!(toks->type == OP && !ft_strcmp(toks->text, ")")))
			toks = toks->next;
		match_redir(toks->next);
	}
	else if (type == CMD)
	{ 
		int flag = 0;
		if (toks->type == WORD)
		{
			while (toks && toks->type == WORD)
				toks = toks->next;
			flag = 1;
		}
		if (is_redir(toks))
			match_redir(toks);
		if (!flag)
		{
			while (toks)
			{
				if (toks->type == OP)
					err_exit(ERR_MSG);
				toks = toks->next;
			}
		}
	}
}

void	check_syntax(t_tree *root)
{
	if (!root)
		return ;
	check_left_node(root);
	check_right_node(root);
	check_node(root);
	check_syntax(root->left);
	check_syntax(root->right);
}
