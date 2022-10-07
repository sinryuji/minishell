/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:03:53 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/07 21:39:04 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	built_in(char *cmd, char **argv, t_env_list *envl)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (ft_echo(argv, envl));
	if (ft_strcmp("cd", cmd) == 0)
		return (ft_cd(argv, envl));
	if (ft_strcmp("pwd", cmd) == 0)
		return (ft_pwd(argv, envl));
	if (ft_strcmp("export", cmd) == 0)
		return (ft_export(argv, envl));
	if (ft_strcmp("unset", cmd) == 0)
		return (ft_unset(argv, envl));
	if (ft_strcmp("env", cmd) == 0)
		return (ft_env(argv, envl));
	if (ft_strcmp("exit", cmd) == 0)
		return (ft_exit(argv, envl));
	return (-1);
}
