/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:55:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 16:46:19 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

static int	option_check(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(int argc, char **argv, t_env_list *envl)
{
	int	option;

	(void)envl;
	if (argc == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	option = option_check(argv[1]);
	argv++;
	if (option)
		argv++;
	while (*argv)
	{
		if (*(argv + 1))
			printf("%s ", *argv);
		else
			printf("%s", *argv);
		argv++;
	}
	if (!option)
		printf("\n");
	return (EXIT_SUCCESS);
}
