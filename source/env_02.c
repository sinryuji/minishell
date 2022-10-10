/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:21:12 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 21:03:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

void	free_env(t_env *env)
{
	free(env->key);
	env->key = NULL;
	if (env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	free(env);
	env = NULL;
}

int	replace_env(t_env_list **envl, t_env *new)
{
	if (!*envl || !new)
		return (FAILURE);
	if (new->value)
	{
		free(get_env(*envl, new->key)->value);
		get_env(*envl, new->key)->value = new->value;
		free(new->key);
		free(new);
	}
	else
		free_env(new);
	return (SUCCESS);
}

int	sort_env(t_env_list **envl)
{
	t_env	*end;
	t_env	*cur;

	if (!*envl)
		return (FAILURE);
	end = (*envl)->tail;
	while (end != (*envl)->head->next)
	{
		cur = (*envl)->head;
		while (cur->next && cur->next != end)
		{
			if (ft_strcmp(cur->key, cur->next->key) > 0)
			{
				swap_str(&cur->key, &cur->next->key);
				swap_str(&cur->value, &cur->next->value);
			}
			cur = cur->next;
		}
		end = end->prev;
	}
	return (SUCCESS);
}

int	get_envlen(t_env_list *envl)
{
	int		i;
	t_env	*env;

	i = 0;
	if (!envl)
		return (FAILURE);
	env = envl->head;
	if (!env)
		return (FAILURE);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**reverse_env(t_env_list *envl)
{
	char	**ret;
	t_env	*env;
	char	*tmp;
	int		i;

	if (!envl)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (get_envlen(envl) + 1));
	env = envl->head;
	if (!env)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ret[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
