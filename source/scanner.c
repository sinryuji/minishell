/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 14:33:34 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scanner.h"
#include "../libft/include/libft.h"

int	is_op(char c)
{
	return (c == '|' || c == '&' || \
			c == '(' || c == ')' || \
			c == '<' || c == '>');
}

int	is_delim(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	find_op(char *script)
{
	char	next;

	next = *(script + 1);
	if (*script == next && next != '(' && next != ')')
		return (1);
	return (0);
}

void	ctl_quote_flag(char *flag, char c)
{
	if (*flag ^ D_QUOTE && c == '\'')
		(*flag) ^= S_QUOTE;
	else if (*flag ^ S_QUOTE && c == '\"')
		(*flag) ^= D_QUOTE;
}

void	scanner(t_token **toks, char *script)
{
	char	flag;
	t_buf	buf;

	flag = 0;
	init_buf(&buf);
	while (*script)
	{
		ctl_quote_flag(&flag, *script);
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
