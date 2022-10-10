/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/10 13:52:32 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "../include/parser.h"

t_tree	*get_new_node(int type, int flag, t_token *toks)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = type;
	node->flag = flag;
	node->toks = toks;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	find_root(t_token *toks, t_tree **root)
{
}

void	parser(t_token *toks, t_tree *root)
{
	find_root(toks, root);
}
