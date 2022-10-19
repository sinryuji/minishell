/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:59:37 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/19 22:32:11 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"

/**/

static void	split_token(t_token **toks, int start)
{
	int		i;
	char	*old_text;
	char	*new_text;
	t_token	*parent;
	t_token *child;

	old_text = ft_substr((*toks)->text, 0, start);
	i = 0;
	while (is_delim((*toks)->text[start + i]))
		i++;
	new_text = ft_substr((*toks)->text, start + i,\
		ft_strlen((*toks)->text) - start - i);
	parent = get_new_token((*toks)->type, old_text);
	child = get_new_token((*toks)->type, new_text);
	parent->next = child;
	child->prev = parent;
	parent->prev = (*toks)->prev;
	child->next = (*toks)->next;
	(*toks)->prev->next = parent;
	(*toks)->next->prev = child;
	free((*toks)->text);
	free(*toks);
	toks = &child;
}

void	split_field(t_tree *root)
{
	int		i;
	char	flag;
	t_token	*toks;

	flag = 0;
	toks = root->toks;
	while (toks)
	{
		if (toks->type == WORD)
		{
			i = 0;
			while (toks->text[i])
			{
				ctl_quote_flag(&flag, toks->text[i]);
				if (!(flag & S_QUOTE + D_QUOTE) && is_delim(toks->text[i]))
				{
					split_token(&toks, i);
					break ;
				}
				i++;
			}
		}
		toks = toks->next;
	}
}
