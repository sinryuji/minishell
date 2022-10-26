/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:41:20 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/26 18:07:56 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/minishell.h"

t_tree	*get_sibilng_node(t_tree *root)

{
	if (root == NULL || root->parent == NULL)
		return (NULL);
	if (root->parent->left == root)
		return (root->parent->right);
	else if (root->parent->right == root)
		return (root->parent->left);
	else
		return (NULL);
}

void	root_free(t_tree *root)
{
	t_token	*tmp;

	if (root == NULL)
		return ;
	root_free(root->left);
	root_free(root->right);
	while (root->toks)
	{
		tmp = root->toks;
		root->toks = root->toks->next;
		free(tmp->text);
		free(tmp);
	}
	free(root);
}
