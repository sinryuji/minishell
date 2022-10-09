/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:05:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/09 20:59:46 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

t_env	*copy_env(t_env *env)
{
	t_env	*new;

	if (!env)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(env->key);
	new->value = ft_strdup(env->value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env_list	*copy_envl(t_env_list *envl)
{
	t_env_list	*new;
	t_env		*env;

	if (!envl)
		return (NULL);
	env = envl->head;
	if (!env)
		return (NULL);
	new = NULL;
	while (env)
	{
		set_env(&new, copy_env(env));
		env = env->next;
	}
	return (new);
}

void	free_envl(t_env_list **envl)
{
	t_env	*env;
	t_env	*tmp;

	if (!*envl)
		return ;
	env = (*envl)->head;
	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp)
			free_env(tmp);
	}
	if (*envl)
		free(*envl);
	*envl = NULL;
}
