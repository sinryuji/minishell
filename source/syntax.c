/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:45:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 17:51:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

int	is_redir(t_token *toks)
{
	return (toks && toks->type == OP && \
			(!ft_strcmp(toks->text, ">") || \
			!ft_strcmp(toks->text, "<") || \
			!ft_strcmp(toks->text, ">>") || \
			!ft_strcmp(toks->text, "<<")));
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
