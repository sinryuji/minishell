/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:59 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 18:05:27 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	argc_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

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

int	ft_exit(char **argv, t_env_list *envl)
{
	if (!*argv)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (!numeric_check(argv[0]))
		// 스트링 빌더를 위해 보류
		ft_puterr(SHELL_NAME": exit: argv[0]: numeric argument required\n");
	else if (argc_check(argv) != 1)
	{
		printf(SHELL_NAME": exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else
		exit(ft_atoi(argv[0]));
	return (EXIT_SUCCESS);
}
