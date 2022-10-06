/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:33:06 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 15:12:58 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "env.h"

int	ft_echo(char **argv, t_env_list *envl);
int	ft_cd(char **argv, t_env_list *envl);
int	ft_pwd(char **argv, t_env_list *envl);
int	ft_export(char **argv, t_env_list *envl);
int	ft_unset(char **argv, t_env_list *envl);
int	ft_env(char **argv, t_env_list *envl);
int	ft_exit(char **argv, t_env_list *envl);

#endif
