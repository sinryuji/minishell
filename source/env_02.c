/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:21:12 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 23:39:28 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

void	free_env(t_env *env)
{
	free(env->key);
	if (env->value)
		free(env->value);
	free(env);
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
	char	*tmp;

	if (!*envl)
		return (FAILURE);
	end = (*envl)->tail;
	while (end != (*envl)->head)
	{
		cur = (*envl)->head;
		while (cur->next)
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
