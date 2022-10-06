/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:00:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 15:14:04 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include "../include/env.h"

int	ft_unset(char **argv, t_env_list *envl)
{
	t_env	*env;
	
	if (!argv[0])
		return (EXIT_FAILURE);
	env = get_env(envl, argv[0]);
	if (!env)
		return (EXIT_FAILURE);
	del_env(&envl, argv[0]);
	return (EXIT_SUCCESS);
}
