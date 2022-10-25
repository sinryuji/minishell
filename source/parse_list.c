/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:16:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:24:01 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

static int	is_line_op(char *str)
{
	return (!(ft_strcmp(str, "&&") && ft_strcmp(str, "||")));
}

static int	is_paren(char *str)
{
	return (!(ft_strcmp(str, "(") && ft_strcmp(str, ")")));
}

static void	parse_list_loop(
		t_token **toks, t_tree *root, t_token **tmp, int *success
		)
{
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN) \
				&& is_line_op((*toks)->text))
		{
			root->flag |= FOUND;
			*success = SUCCESS;
			break ;
		}
		else if ((*toks)->type == OP && is_paren((*toks)->text))
			root->flag ^= PAREN;
		if ((*toks)->prev == NULL)
			*tmp = *toks;
		*toks = (*toks)->prev;
	}
}

int	parse_list(t_tree *root)
{
	int		success;
	t_token	*toks;
	t_token	*tmp;

	toks = root->toks;
	success = 0;
	parse_list_loop(&toks, root, &tmp, &success);
	if (root->flag & PAREN)
		return (FALSE);
	if (!success)
	{
		toks = tmp;
		root->type = PIPELINE;
	}
	root->toks = toks;
	return (TRUE);
}
