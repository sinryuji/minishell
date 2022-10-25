/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:00:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 20:49:39 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"
#include <stdlib.h>

int	ft_unset(int argc, char **argv, t_env_list *envl)
{
	int	i;
	int	ret;

	if (argc == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		if (key_vaildation(argv[i]) == FALSE)
		{
			put_error_arg(argv[0], argv[i], "not a valid identifier");
			ret = EXIT_FAILURE;
			i++;
			continue ;
		}
		if (del_env(&envl, argv[i]) == FAILURE)
			ret = EXIT_SUCCESS;
		i++;
	}
	return (ret);
}
