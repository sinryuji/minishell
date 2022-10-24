/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:59:37 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/23 20:53:41 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/executor.h"

static t_token	*split_token(t_token *toks, int start)
{
	int		i;
	char	*old_text;
	char	*new_text;
	t_token	*parent;
	t_token *child;

	old_text = ft_substr(toks->text, 0, start);
	i = 0;
	while (is_delim(toks->text[start + i]))
		i++;
	new_text = ft_substr(toks->text, start + i,\
		ft_strlen(toks->text) - start - i);
	parent = get_new_token(toks->type, old_text);
	child = get_new_token(toks->type, new_text);
	parent->next = child;
	child->prev = parent;
	parent->prev = toks->prev;
	child->next = toks->next;
	if (toks->prev)
		toks->prev->next = parent;
	if (toks->next)
		toks->next->prev = child;
	free(toks->text);
	free(toks);
	return (parent);
}

void	split_field(t_tree *root)
{
	int		i;
	char	flag;
	t_token	*save;

	while (root->toks)
	{
		if (root->toks->type == WORD)
		{
			i = 0;
			flag = 0;
			while (root->toks->text[i])
			{
				ctl_quote_flag(&flag, root->toks->text[i]);
				if (!(flag & S_QUOTE + D_QUOTE) && is_delim(root->toks->text[i]))
				{
					root->toks = split_token(root->toks, i);
					break ;
				}
				i++;
			}
		}
		if (root->toks->next == NULL)
			save = root->toks;
		root->toks = root->toks->next;
	}
	root->toks = get_first_token(save);
}
