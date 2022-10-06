/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:03:53 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 20:17:11 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	built_in(char *cmd, char **argv, t_env_list *envl)
{
	if (!ft_strncmp("echo", cmd, ft_max(ft_strlen("echo"), ft_strlen(cmd))))
		return (ft_echo(argv, envl));
	if (!ft_strncmp("cd", cmd, ft_max(ft_strlen("cd"), ft_strlen(cmd))))
		return (ft_cd(argv, envl));
	if (!ft_strncmp("pwd", cmd, ft_max(ft_strlen("pwd"), ft_strlen(cmd))))
		return (ft_pwd(argv, envl));
	if (!ft_strncmp("export", cmd, ft_max(ft_strlen("export"), ft_strlen(cmd))))
		return (ft_export(argv, envl));
	if (!ft_strncmp("unset", cmd, ft_max(ft_strlen("unset"), ft_strlen(cmd))))
		return (ft_unset(argv, envl));
	if (!ft_strncmp("env", cmd, ft_max(ft_strlen("env"), ft_strlen(cmd))))
		return (ft_env(argv, envl));
	if (!ft_strncmp("exit", cmd, ft_max(ft_strlen("exit"), ft_strlen(cmd))))
		return (ft_exit(argv, envl));
	return (-1);
}
