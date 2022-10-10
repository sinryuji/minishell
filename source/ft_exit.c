/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:59 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 12:22:43 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	numeric_check(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (FALSE);
		arg++;
	}
	return (TRUE);
}

int	ft_exit(int argc, char **argv, t_env_list *envl)
{
	(void)envl;
	printf("exit\n");
	if (argc == 1)
		exit(EXIT_SUCCESS);
	else if (numeric_check(argv[1]) == FALSE)
	{
		put_error_arg(argv[0], argv[1], "numeric argument required");
		exit(255);
	}
	else if (argc > 2)
	{
		ft_putendl_fd(SHELL_NAME": exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		exit(ft_atoi(argv[1]));
}
