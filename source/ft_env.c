/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:34:51 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 18:18:38 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	print_env(t_env_list *envl)
{
	t_env	*env;

	env = envl->head;
	if (!env)
		return (0);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (1);
}

int	ft_env(char **argv, t_env_list *envl)
{
	if (!*argv)
		print_env(envl);
	else
		processing(argv, envl);
	return (EXIT_SUCCESS);
}
