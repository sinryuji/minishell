/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:41:23 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 22:41:47 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include <stdlib.h>

static void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	sort_env(t_env_list **envl)
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

static int	print_export(t_env_list *envl)
{
	t_env	*env;

	if (!envl)
		return (FAILURE);
	env = envl->head;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}	
	return (SUCCESS);
}

int	ft_export(int argc, char **argv, t_env_list *envl)
{
	char	**ret;
	t_env	*new;

	if (argc == 1)
	{
		if (sort_env(&envl) == FAILURE)
			return (EXIT_FAILURE);
		if (print_export(envl) == FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (key_vaildation(argv[1]) == FAILURE)
		{
			put_error(argv[0], argv[1], "not a valid identifier");
			return (EXIT_FAILURE);
		}
		if (!set_env(&envl, new_env(argv[1])))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
