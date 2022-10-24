/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:19:25 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/24 16:36:01 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/executor.h"

void	expand(t_tree *root, t_env_list *envl)
{
	if (root->type != CMD)
		return ;
	(void)envl;
	expand_env(root, envl);
	split_field(root);
	expand_pathname(root);
	quote_removal(root);
}
