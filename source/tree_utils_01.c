/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:15:49 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 15:19:13 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/parser.h"
#include "../include/minishell.h"

t_tree	*get_new_node(int type, int flag, t_token *toks, t_tree *parent)
{
	t_tree	*node;

	if (!toks)
		return (NULL);
	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = type;
	node->flag = flag;
	node->toks = toks;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return (node);
}

t_tree	*make_left_node(t_tree *root)
{
	t_tree	*new;
	t_token	*toks;

	new = NULL;
	toks = root->toks;
	if (root == NULL)
		return (NULL);
	if (root->flag & FOUND)
	{
		if (toks->prev == NULL)
			return (NULL);
		toks->prev->next = NULL;
		if (root->type == LIST)
			new = get_new_node(LIST, 0, toks->prev, root);
		if (root->type == PIPELINE)
			new = get_new_node(CMD, 0, get_first_token(toks), root);
	}
	return (new);
}

t_tree	*make_right_node(t_tree *root)
{
	t_tree	*new;
	t_token	*toks;

	new = NULL;
	toks = root->toks;
	if (root == NULL)
		return (NULL);
	if (root->flag & FOUND)
	{
		if (toks->next)
			toks->next->prev = NULL;
		new = get_new_node(PIPELINE, 0, toks->next, root);
//=======
//		if (toks->next == NULL)
//			return (NULL);
//		if (root->type == LIST)
//		{
//			if (toks->next)
//				toks->next->prev = NULL;
//			new = get_new_node(PIPELINE, 0, toks->next);
//		}
//		else if (root->type == PIPELINE)
//			new = get_new_node(CMD, 0, toks->next);
//>>>>>>> main
	}
	return (new);
}

void	make_root_node(t_tree **root)
{
	t_token	*toks;

	toks = (*root)->toks;
	if ((*root)->flag & FOUND)
	{
		if ((*root)->type == LIST)
			(*root)->type = CTLOP;
		if ((*root)->type == PIPELINE)
			(*root)->type = PIPE;
		toks->next = NULL;
		toks->prev = NULL;
		(*root)->toks = toks;
	}
}

int	who_am_i(t_tree *root)
{
	if (root->parent == NULL)
		return (ROOT);
	else if (root->parent->left == root)
		return (LEFT);
	else
		return (RIGHT);
}
