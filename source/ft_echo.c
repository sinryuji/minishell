/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:55:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/27 14:06:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

static int	option_check(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
			if ((int)ft_strlen(arg) == i)
				return (TRUE);
		}
	}
	return (FALSE);
}

static void	print_echo(char **argv, int i)
{
	while (argv[i])
	{
		if (argv[i + 1])
			printf("%s ", argv[i]);
		else
			printf("%s", argv[i]);
		i++;
	}
}

int	ft_echo(int argc, char **argv, t_env_list *envl)
{
	int	option;
	int	i;

	(void)envl;
	if (argc == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	i = 1;
	option = FALSE;
	while (argv[i] != NULL && argv[i][0] == '-')
	{
		if (option_check(argv[i]) == TRUE)
			option = TRUE;
		else
			break ;
		i++;
	}
	print_echo(argv, i);
	if (!option)
		printf("\n");
	return (EXIT_SUCCESS);
}
