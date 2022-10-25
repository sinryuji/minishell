/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:39:20 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 03:24:49 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/executor.h"
#include "../libft/include/libft.h"
#include "../include/minishell.h"

static char	*get_mid_str(char *key, t_env_list *envl)
{
	char	*mid;

	if (!ft_strncmp(key, "?", 1))
		mid = ft_strjoin(ft_itoa(g_exit_code), key + 1);
	else if (!ft_strcmp(key, "$"))
		mid = ft_strdup("$$");
	else
		mid = get_env_val(get_env(envl, key));
	return (mid);
}

static void	replace_text_addr(int *i, t_new_str *str, t_token *toks)
{
	if (str->mid != NULL)
	{
		*i = ft_strlen(str->mid);
		toks->text = strjoin_3way(str->pre, str->mid, str->post);
	}
	else
	{
		*i = 0;
		toks->text = ft_strjoin(str->pre, str->post);
	}
}

static int	replace_text(t_token *toks, int start, t_env_list *envl)
{
	int			i;
	char		*key;
	t_new_str	str;

	i = start;
	while (toks->text[i] && is_allowed(toks->text[i]))
		i++;
	if (i == start)
		return (i);
	key = ft_strndup(toks->text + start, i - start);
	str.mid = get_mid_str(key, envl);
	str.pre = ft_substr(toks->text, 0, start - 1);
	str.post = ft_substr(toks->text, i, ft_strlen(toks->text) - i);
	free(toks->text);
	replace_text_addr(&i, &str, toks);
	(free(str.pre), free(str.post), free(key));
	return (i);
}

void	expand_env(t_tree *root, t_env_list *envl)
{
	int		i;
	char	flag;
	t_token	*toks;

	toks = root->toks;
	while (toks)
	{
		if (toks->type == WORD)
		{
			i = 0;
			flag = 0;
			while (toks->text[i])
			{
				ctl_quote_flag(&flag, toks->text[i]);
				if (!(flag & S_QUOTE) && toks->text[i] == '$')
				{
					i += replace_text(toks, i + 1, envl);
					continue ;
				}
				i++;
			}
		}
		toks = toks->next;
	}
}
