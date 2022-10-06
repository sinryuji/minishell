/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:16:30 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/06 11:51:42 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	ft_cd(int argc, char **argv, t_env_list *envl)
{
	(void)argc;
	(void)envl;
	if (chdir(argv[0]) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
