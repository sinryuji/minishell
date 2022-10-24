/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:54:58 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/24 14:49:03 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "../libft/include/libft.h"
#include "../include/executor.h"

char	*get_chunk(t_token *toks, int *i)
{
	int		start;
	char	flag;

	flag = 0;
	if (toks->text[*i] == '\'')
		flag |= S_QUOTE;
	else
		flag |= D_QUOTE;
	start = ++(*i);
	while (1)
	{
		if ((flag & S_QUOTE && toks->text[*i] == '\'') || \
				(flag & D_QUOTE && toks->text[*i] == '\"'))
			break ;
		(*i)++;
	}
	return (ft_strndup(toks->text + start, (size_t)*i - start));
}

static char	*concat(char *dst, char *src)
{
	int		i;
	int		len;
	char	*concated;

	if (!src && !*src)
		return (dst);
	len = 0;
	if (dst && *dst)
		len += ft_strlen(dst);
	len += ft_strlen(src);
	i = 0;
	concated = (char *)malloc(sizeof(char) * ++len);
	while (dst && dst[i])
	{
		concated[i] = dst[i];
		i++;
	}
	while (src && *src)
		concated[i++] = *src++;
	free(dst);
	concated[i] = '\0';
	return (concated);
}


static char	*cat_a_char(char *str, char c)
{
	int		len;
	char	*new;

	if (str && *str)
		len = ft_strlen(str);
	else
		len = 0;
	new = (char *)malloc(sizeof(char) * (len + 2));
	ft_memmove(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

void	quote_removal(t_tree *root)
{
	int		i;
	char	*removed;
	char	*chunk;
	t_token	*toks;

	toks = root->toks;
	while (toks)
	{
		i = 0;
		removed = NULL;
		if (toks->type == WORD || is_redir(toks))
		{
			while (toks->text[i])
			{
				if (toks->text[i] == '\"' || toks->text[i] == '\'')
				{
					chunk = get_chunk(toks, &i);
					removed = concat(removed, chunk);
					free(chunk);
				}
				else
					removed = cat_a_char(removed, toks->text[i]);
				i++;
			}
		}
		if (i)
		{
			free(toks->text);
			toks->text = removed;
		}
		toks = toks->next;
	}
}

