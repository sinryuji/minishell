/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:41:23 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 14:56:31 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	sort_env(t_env_list **envl)
{
	t_env	*end;
	t_env	*cur;
	char	*tmp;

	if (!*envl)
		return (0);
	end = (*envl)->tail;
	while (end != (*envl)->head)
	{
		cur = (*envl)->head;
		while (cur->next)
		{
			if (ft_strncmp(cur->key, cur->next->key, \
						ft_max(ft_strlen(cur->key), \
							ft_strlen(cur->next->key))) > 0)
			{
				swap_str(&cur->key, &cur->next->key);
				swap_str(&cur->value, &cur->next->value);
			}
			cur = cur->next;
		}
		end = end->prev;
	}
	return (1);
}

int	print_export(t_env_list *envl)
{
	t_env	*env;

	if (!envl)
		return (0);
	env = envl->head;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}	
	return (1);
}

int	key_vaildation(char *key)
{
	while (*key)
	{
		if (!ft_isalnum(*key))
			return (0);
		key++;
	}
	return (1);
}

int	ft_export(int argc, char **argv, t_env_list *envl)
{
	char	**ret;
	t_env	*new;

	if (argc == 0)
	{
		if (!sort_env(&envl))
			return (EXIT_FAILURE);
		if (!print_export(envl))
			return (EXIT_FAILURE);
	}
	else
	{
		new = new_env(argv[0]);
		if (!key_vaildation(new->key))
			// 일단 보류
			ft_puterr(SHELL_NAME": export: ` ': not a valid identifier\n");
		if (!set_env(&envl, new_env(argv[0])))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
