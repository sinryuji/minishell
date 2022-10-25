/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:19:25 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:24:07 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

static void	parse_pipeline_loop(t_token **toks, t_tree *root, int *success)
{
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN) && \
				!ft_strcmp((*toks)->text, "|"))
		{
			root->flag |= FOUND;
			root->toks = *toks;
			*success = 1;
			break ;
		}
		else if ((*toks)->type == OP && \
				(!ft_strcmp((*toks)->text, "(") || \
				!ft_strcmp((*toks)->text, ")")))
			(root->flag) ^= PAREN;
		*toks = (*toks)->next;
	}
}

int	parse_pipeline(t_tree *root)
{
	int		success;
	t_token	*toks;
	t_token	*origin;

	success = 0;
	toks = root->toks;
	origin = toks;
	parse_pipeline_loop(&toks, root, &success);
	if (root->flag & PAREN)
		return (FALSE);
	if (!success)
	{
		toks = origin;
		root->type = CMD;
	}
	return (TRUE);
}
