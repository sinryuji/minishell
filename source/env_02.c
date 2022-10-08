/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:21:12 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 22:39:24 by hyeongki         ###   ########.fr       */
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
