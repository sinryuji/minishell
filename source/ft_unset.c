/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:00:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 16:52:20 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

int	ft_unset(int argc, char **argv, t_env_list *envl)
{
	t_env	*env;

	if (argc == 1)
		return (EXIT_SUCCESS);
	env = get_env(envl, argv[1]);
	if (!env)
		return (EXIT_FAILURE);
	del_env(&envl, argv[1]);
	return (EXIT_SUCCESS);
}
