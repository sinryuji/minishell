/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:03:53 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/09 18:10:38 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"

t_built_in get_built_in(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (&ft_echo);
	else if (ft_strcmp("cd", cmd) == 0)
		return (&ft_cd);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (&ft_pwd);
	else if (ft_strcmp("export", cmd) == 0)
		return (&ft_export);
	else if (ft_strcmp("unset", cmd) == 0)
		return (&ft_unset);
	else if (ft_strcmp("env", cmd) == 0)
		return (&ft_env);
	else if (ft_strcmp("exit", cmd) == 0)
		return (&ft_exit);
	else
		return (NULL);
}

int	key_vaildation(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (FALSE);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (FALSE);
		key++;
	}
	return (TRUE);
}
