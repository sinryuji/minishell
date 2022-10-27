/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:39:20 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/27 14:42:16 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/executor.h"
#include "../libft/include/libft.h"
#include "../include/minishell.h"

static char	*get_mid_str(char *key, t_env_list *envl)
{
	char	*mid;
	char	*tmp;

	if (!ft_strncmp(key, "?", 1))
	{
		tmp = ft_itoa(g_exit_code);
		mid = ft_strjoin(tmp, key + 1);
		free(tmp);
	}
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
	int			mid_free;

	i = start;
	while (toks->text[i] && is_allowed(toks->text[i]))
		i++;
	if (i == start)
		return (i);
	key = ft_strndup(toks->text + start, i - start);
	mid_free = FALSE;
	if (!ft_strcmp(key, "?") | !ft_strcmp(key, "$"))
		mid_free = TRUE;
	str.mid = get_mid_str(key, envl);
	str.pre = ft_substr(toks->text, 0, start - 1);
	str.post = ft_substr(toks->text, i, ft_strlen(toks->text) - i);
	free(toks->text);
	replace_text_addr(&i, &str, toks);
	(free(str.pre), free(str.post), free(key));
	if (mid_free == TRUE)
		free(str.mid);
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
