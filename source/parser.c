/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:21:51 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

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
