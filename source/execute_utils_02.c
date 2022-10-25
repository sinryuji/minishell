/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:13 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 20:07:15 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_child(void)
{
	int		status;
	int		sig;
	int		i;

	i = 0;
	set_signal(IGN, IGN);
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT && i == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (sig == SIGQUIT && i == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_code = sig + 128;
			i++;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
	set_signal(HAN, HAN);
}

void	set_exit_code(int exit_code)
{
	g_exit_code = exit_code;
	ft_putendl_fd("systax err\n", STDERR_FILENO);
	exit(g_exit_code);
}
