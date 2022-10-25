/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:20:08 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:23:49 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

int	parse_cmd(t_tree *root)
{
	int		subsh;
	t_token	*origin;
	t_token	*toks;

	toks = root->toks;
	origin = toks;
	subsh = FALSE;
	while (toks)
	{
		if (toks->type == OP && \
			(!ft_strcmp(toks->text, "(") || \
			!ft_strcmp(toks->text, ")")))
		{
			(root->flag) ^= PAREN;
			subsh = TRUE;
		}
		toks = toks->next;
	}
	if (root->flag & PAREN)
		return (FALSE);
	else if (subsh == TRUE)
		root->type = SUBSH;
	toks = origin;
	return (TRUE);
}
