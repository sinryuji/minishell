/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:13:21 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 17:59:44 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

static int	match_redir(t_token **toks)
{
	t_token *origin;

	origin = *toks;
	while (*toks)
	{
		if (is_redir(*toks))
		{
			if (!(*toks)->next || (*toks)->next->type != WORD)
				return (FALSE);
		}
		else
			break ;
		*toks = (*toks)->next->next;
	}
	*toks = origin;
	return (TRUE);
}

static int	check_node_subsh(t_token **toks)
{
	if (!((*toks)->type == OP && !ft_strcmp((*toks)->text, "(")))
		return (FALSE);
	while (!((*toks)->type == OP && !ft_strcmp((*toks)->text, ")")))
		*toks = (*toks)->next;
	if (!match_redir(&((*toks)->next)))
		return (FALSE);
	return (TRUE);
}

static int	check_node_cmd(t_token **toks)
{
	while (*toks)
	{
		if ((*toks)->type == WORD)
		{
			while (*toks && (*toks)->type == WORD)
				*toks = (*toks)->next;
		}
		if (is_redir(*toks))
		{
			if (!match_redir(&(*toks)))
				return (FALSE);
		}
		if (*toks)
			*toks = (*toks)->next;
	}
	return (TRUE);
}

int	check_node(t_tree *root)
{
	t_token		*toks;
	const int	type = root->type;

	toks = root->toks;
	if (type == SUBSH)
	{
		if (!check_node_subsh(&toks))
			return (FALSE);
	}
	else if (type == CMD)
	{
		if (!check_node_cmd(&toks))
			return (FALSE);
	}
	return (TRUE);
}
