/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:30:46 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 14:17:49 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

t_env	*new_env(char *key_val)
{
	t_env	*new;
	char	*equl;

	if (!key_val)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equl = ft_strchr(key_val, '=');
	if (equl)
	{
		new->key = ft_strndup(key_val, equl - key_val);
		new->value = ft_strdup(equl + 1);
	}
	else
	{
		new->key = key_val;
		new->value = NULL;
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	del_env(t_env_list **envl, char *key)
{
	t_env	*env;

	env = get_env(*envl, key);
	if (!env)
		return (0);
	if (env == (*envl)->head)
	{
		env->next->prev = NULL;
		(*envl)->head = env->next;
	}
	else if (env == (*envl)->tail)
	{
		env->prev->next = NULL;
		(*envl)->tail = env->prev;
	}
	else
	{
		env->prev->next = env->next;
		env->next->prev = env->prev;
	}
	free(env->key);
	free(env->value);
	free(env);
	return (1);
}

int	set_env(t_env_list **envl, t_env *new)
{
	if (!*envl)
	{
		*envl = (t_env_list *)malloc(sizeof(t_env_list));
		if (!*envl)
			return (0);
		(*envl)->head = new;
		(*envl)->tail = new;
	}
	else if (get_env(*envl, new->key))
	{
		if (new->value)
			get_env(*envl, new->key)->value = new->value;
		free(new);
	}
	else
	{
		(*envl)->tail->next = new;
		new->prev = (*envl)->tail;
		(*envl)->tail = new;
	}
	return (1);
}

t_env	*get_env(t_env_list *envl, char *key)
{
	t_env	*env;

	env = envl->head;
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	parse_env(t_env_list **envl, char **envp)
{
	if (!envp)
		return (0);
	while (*envp)
	{
		if (!set_env(envl, new_env(*envp)))
			return (0);
		envp++;
	}
	return (1);
}
