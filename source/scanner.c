/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/06 20:50:44 by jiwahn           ###   ########.fr       */
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

#include <stdio.h>
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
	char		flag;
	t_buf	buf;

	flag = 0;
	init_buf(&buf);
	while (*script)
	{
		if (flag ^ D_QUOTE && *script == '\'')
			flag ^= S_QUOTE;
		else if (flag ^ S_QUOTE && *script == '\"')
			flag ^= D_QUOTE;
		else if ((flag ^ S_QUOTE) && (flag ^ D_QUOTE) && is_delim(*script))
			flush_buf(toks, &buf);
		else if ((flag ^ S_QUOTE) && (flag ^ D_QUOTE) && is_op(*script))
		{
			flush_buf(toks, &buf);
			if (find_op(script))
			{
				tok_add_back(toks, get_new_token(OP, ft_strndup(script, 2)));
				script++;
			}
			else
				tok_add_back(toks, get_new_token(OP, ft_strndup(script, 1)));
		}
		else if (flag ^ S_QUOTE && *script == '$' && \
				!is_delim(*(script + 1)) && (ft_isalnum(*(script + 1)) || *(script + 1) == '?'))
		{
			flush_buf(toks, &buf);
			tok_add_back(toks, get_new_token(OP, ft_strndup("$", 1)));
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

#include <readline/readline.h>
#include <stdio.h>
void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("[%d]%s->", toks->type, toks->text);
		toks = toks->next;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	t_token		*toks;
	char		*input;

	toks = NULL;
	input = readline("input>> ");
	scanner(&toks, input);
	print_toks(toks);
	system("leaks a.out");
	free(input);
	return (0);
}
