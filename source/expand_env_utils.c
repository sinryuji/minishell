/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:23:43 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 03:24:53 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../libft/include/libft.h"
#include "../include/minishell.h"

int	is_allowed(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?' || c == '$');
}

char	*get_env_val(t_env *env)
{
	if (env == NULL)
		return (NULL);
	else
		return (env->value);
}

char	*strjoin_3way(char *pre, char *mid, char *post)
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
