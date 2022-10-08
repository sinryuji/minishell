/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:41:23 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 23:42:58 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include <stdlib.h>

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

static int	append_export(char **argv, t_env_list *envl)
{
	t_env	*new;
	int		i;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	while (argv[++i])
	{
		new = new_env(argv[i]);
		if (key_vaildation(new->key) == FAILURE)
		{
			put_error(argv[0], argv[i], "not a valid identifier");
			ret = EXIT_FAILURE;
			free_env(new);
		}
		else if (set_env(&envl, new) == FAILURE)
			free_env(new);
	}
	return (ret);
}

int	ft_export(int argc, char **argv, t_env_list *envl)
{
	char	**ret;

	if (argc == 1)
	{
		if (sort_env(&envl) == FAILURE)
			return (EXIT_FAILURE);
		if (print_export(envl) == FAILURE)
			return (EXIT_FAILURE);
	}
	else
		return (append_export(argv, envl));
	return (EXIT_SUCCESS);
}
