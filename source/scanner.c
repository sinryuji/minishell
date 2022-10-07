/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/07 15:49:09 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "../include/scanner.h"
#include "../libft/include/libft.h"

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

void	scanner(t_token **toks, char *script)
{
	char	flag;
	t_buf	buf;

	flag = 0;
	init_buf(&buf);
	while (*script)
	{
		if (flag ^ D_QUOTE && *script == '\'')
			flag ^= S_QUOTE;
		else if (flag ^ S_QUOTE && *script == '\"')
			flag ^= D_QUOTE;
		if (!(flag & S_QUOTE + D_QUOTE) && is_delim(*script))
			flush_buf(toks, &buf);
		else if (!(flag & S_QUOTE + D_QUOTE) && is_op(*script))
		{
			flush_buf(toks, &buf);
			if (find_op(script))
				tok_add_back(toks, get_new_token(OP, ft_strndup(script++, 2)));
			else
				tok_add_back(toks, get_new_token(OP, ft_strndup(script, 1)));
		}
		else
			append_to_buf(*script, &buf);
		script++;
	}
	if (flag & S_QUOTE || flag & D_QUOTE)
		err_exit("syntax err\n");
	flush_buf(toks, &buf);
	free(buf.word);
}
