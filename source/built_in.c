/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:03:53 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 23:25:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	built_in(int argc, char **argv, t_env_list *envl)
{
	if (ft_strcmp("echo", argv[0]) == 0)
		return (ft_echo(argc, argv, envl));
	if (ft_strcmp("cd", argv[0]) == 0)
		return (ft_cd(argc, argv, envl));
	if (ft_strcmp("pwd", argv[0]) == 0)
		return (ft_pwd(argc, argv, envl));
	if (ft_strcmp("export", argv[0]) == 0)
		return (ft_export(argc, argv, envl));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (ft_unset(argc, argv, envl));
	if (ft_strcmp("env", argv[0]) == 0)
		return (ft_env(argc, argv, envl));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (ft_exit(argc, argv, envl));
	return (-1);
}

int	key_vaildation(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (FALSE);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (FALSE);
		key++;
	}
	return (TRUE);
}
