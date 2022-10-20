/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:19:25 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/20 13:17:53 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/executor.h"
#include "../libft/include/libft.h"

void	quote_removal(t_tree *root)
{
	t_token	*toks;

	toks = root->toks;
	while (toks)
	{
		if (toks->type == WORD)
		{
		}
		toks = toks->next;
	}
}

void	expand(t_tree *root, t_env_list *envl)
{
	if (root == NULL)
		return ;
	expand(root->left, envl);
	if (root->type != CMD)
		return ;
	expand_env(root, envl);
	split_field(root);
	expand_pathname(root);
	quote_removal(root);
	expand(root->right, envl);
}
