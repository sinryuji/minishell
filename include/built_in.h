/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:33:06 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/04 21:43:12 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int	ft_echo(int argc, char **argv, char **envp);
int	ft_cd(int argc, char **argv, char **envp);
int	ft_pwd(int argc, char **argv, char **envp);
int	ft_export(int argc, char **argv, char **envp);
int	ft_unset(int agrc, char **argv, char **envp);
int	ft_env(int agrc, char **argv, char **envp);
int	ft_exit(int argc, char **argv, char **envp);

#endif
