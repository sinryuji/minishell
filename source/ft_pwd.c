/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:12:59 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/10 12:21:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

int	ft_pwd(int argc, char **argv, t_env_list *envl)
{
	char	*path;

	(void)argc;
	(void)envl;
	(void)argv;
	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
