/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:43:17 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 17:43:22 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/scanner.h"

t_token	*get_new_token(int type, char *text)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = type;
	new_token->text = text;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	tok_add_back(t_token **toks, t_token *new)
{
	t_token	*p;

	p = *toks;
	if (new == NULL)
		return ;
	if (*toks == NULL && new != NULL)
	{
		*toks = new;
		return ;
	}
	while ((*toks)->next)
		*toks = (*toks)->next;
	new->prev = *toks;
	(*toks)->next = new;
	*toks = p;
}

t_token	*get_last_token(t_token *toks)
{
	if (!toks)
		return (NULL);
	while (toks->next)
		toks = toks->next;
	return (toks);
}

t_token	*get_first_token(t_token *toks)
{
	if (!toks)
		return (NULL);
	while (toks && toks->prev)
		toks = toks->prev;
	return (toks);
}

void	free_toks(t_token **toks)
{
	t_token	*tmp;

	while (*toks)
	{
		tmp = *toks;
		free((*toks)->text);
		*toks = (*toks)->next;
		free(tmp);
	}
}
