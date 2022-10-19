/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:39:20 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/19 20:18:10 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/executor.h"
#include "../libft/include/libft.h"

static int	is_allowed(char c)
{
	return (ft_isalnum(c) || c == '-');
}

static char	*get_env_val(t_env *env)
{
	if (env == NULL)
		return (NULL);
	else
		return (env->value);
}

static char	*strjoin_3way(char *pre, char *mid, char *post)
{
	size_t	i;
	size_t	len;
	char	*result;
	
	i = 0;
	len = ft_strlen(pre) + ft_strlen(mid) + ft_strlen(post);
	result = (char *)malloc(sizeof(char) * len + 1);
	while (pre && *pre)
	{
		result[i++] = *pre;
		pre++;
	}
	while (mid && *mid)
	{
		result[i++] = *mid;
		mid++;
	}
	while (post && *post)
	{
		result[i++] = *post;
		post++;
	}
	result[len] = '\0';
	return (result);
}

static int	replace_text(t_token *toks, int start, t_env_list *envl)
{
	int		i;
	char	*key;
	char	*pre;
	char	*mid;
	char	*post;

	i = start;
	while(toks->text[i] && is_allowed(toks->text[i]))
		i++;
	key = ft_strndup(toks->text + start, i - start);
	mid = get_env_val(get_env(envl, key));
	pre = ft_substr(toks->text, 0, start - 1);
	post = ft_substr(toks->text, i, ft_strlen(toks->text) - i);
	free(toks->text);
	if (mid != NULL)
	{
		i = ft_strlen(mid);
		toks->text = strjoin_3way(pre, mid, post);
	}
	else
	{
		i = 0;
		toks->text = ft_strjoin(pre, post);
	}
	free(pre);
	free(post);
	free(key);
	return (i);
}

void	expand_env(t_tree *root, t_env_list *envl)
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

