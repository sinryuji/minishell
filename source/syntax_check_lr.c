/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_lr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:12:28 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 22:24:46 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

int	check_left_node(t_tree *root)
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

int	check_right_node(t_tree *root)
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
