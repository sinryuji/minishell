/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:28:27 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/17 18:30:55 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
		ft_perror_exit("fork error\n");
	if (ret == 0)
		set_signal(DFL, DFL);
	return (ret);
}
