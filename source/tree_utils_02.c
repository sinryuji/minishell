/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:41:20 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 13:16:59 by jiwahn           ###   ########.fr       */
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
