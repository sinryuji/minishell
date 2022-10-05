/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/05 14:44:00 by hyeongki         ###   ########.fr       */
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

# include "../libft/include/libft.h"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_env_list
{
	struct s_env	*head;
	struct s_env	*tail;
}	t_env_list;

#endif
