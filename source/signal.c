/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:47:29 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 20:48:00 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == HAN)
		signal(SIGINT, signal_handler);
	if (sig_quit == HAN)
		signal(SIGQUIT, signal_handler);
	if (sig_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
}
