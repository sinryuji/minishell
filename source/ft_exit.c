/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:59 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 16:36:14 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	numeric_check(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	ft_exit(int argc, char **argv, t_env_list *envl)
{
	if (!*argv)
	{
		printf("exit\n");
		return(EXIT_SUCCESS - 2);
	}
	if (!numeric_check(argv[0]))
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin(SHELL_NAME": exit: ", \
						argv[0]), ": not a valid identifier\n"), 2);
	}
//		ft_puterr(ft_strjoin(ft_strjoin(SHELL_NAME": exit: ", \
//						argv[0]), ": not a valid identifier\n"));
	else if (get_argc(argv) != 1)
	{
		printf(SHELL_NAME": exit: too many arguments\n");
		return (EXIT_FAILURE - 2);
	}
	else
		return(ft_atoi(argv[0]));
	return (EXIT_SUCCESS - 2);
}
