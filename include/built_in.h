/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:33:06 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 16:34:52 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "env.h"

int	built_in(int argc, char **argv, t_env_list *envl);

int	ft_echo(int argc, char **argv, t_env_list *envl);
int	ft_cd(int argc, char **argv, t_env_list *envl);
int	ft_pwd(int argc, char **argv, t_env_list *envl);
int	ft_export(int argc, char **argv, t_env_list *envl);
int	ft_unset(int argc, char **argv, t_env_list *envl);
int	ft_env(int argc, char **argv, t_env_list *envl);
int	ft_exit(int argc, char **argv, t_env_list *envl);

#endif
