/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:00:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/09 18:05:00 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

int	ft_unset(int argc, char **argv, t_env_list *envl)
{
	t_env	*env;

	(void)argc;
	if (argc == 1)
		return (EXIT_SUCCESS);
	if (key_vaildation(argv[1]) == FALSE)
	{
		put_error_arg(argv[0], argv[1], "not a valid identifier");
		return (EXIT_FAILURE);
	}
	if (del_env(&envl, argv[1]) == FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
