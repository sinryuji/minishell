/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:55:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/04 21:55:33 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	option_check(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(int argc, char **argv, char **envp)
{
	int	option;

	(void)argc;
	(void)envp;
	option = option_check(argv[0]);
	if (option)
		argv++;
	while (argv)
	{
		if (argv + 1)
			printf("%s ", *argv);
		else
			printf("%s", *argv);
		argv++;
	}
	if (!option)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
