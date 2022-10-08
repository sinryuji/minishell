/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 18:47:19 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/termios.h>
# include <termios.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

# include "../libft/include/libft.h"
# include "env.h"

# define SHELL_NAME "fdf"
# define SUCCESS 1
# define FAILURE 0

/* main.c */
void	processing(char **argv, t_env_list *envl);

/* error.c */
void	put_error(char *cmd, char *arg, char *strerr);

/* util.c */
int		get_argc(char **argv);

#endif
