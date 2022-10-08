/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:16:30 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/08 21:38:30 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/built_in.h"
#include <stdlib.h>

#define HOME 1
#define OLDPWD 2

static int	put_cd_error(char *arg, char *path, int flag)
{
	if (flag == HOME)
		ft_putendl_fd(SHELL_NAME": cd: HOME net set", STDERR_FILENO);
	else if (flag == OLDPWD)
		ft_putendl_fd(SHELL_NAME": cd: OLDPWD net set", STDERR_FILENO);
	else
		put_error(arg, path, strerror(errno));
	return (EXIT_FAILURE);
}

static int	cd_path(char *path, t_env_list *envl, int flag)
{
	char	*tmp;
	int		ret;
	char	buf[BUFSIZ];

	tmp = NULL;
	getcwd(buf, BUFSIZ);
	tmp = ft_strjoin("OLDPWD=", buf);
	ret = chdir(path);
	if (ret != -1)
	{
		set_env(&envl, new_env(tmp));
		free(tmp);
		getcwd(buf, BUFSIZ);
		tmp = ft_strjoin("PWD=", buf);
		set_env(&envl, new_env(tmp));
	}
	free(tmp);
	if (flag == OLDPWD)
		printf("%s\n", buf);
	return (ret);
}

int	ft_cd(int argc, char **argv, t_env_list *envl)
{
	t_env	*env;
	char	*path;
	int		flag;

	(void)argc;
	env = NULL;
	path = NULL;
	flag = 0;
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
	{
		env = get_env(envl, "HOME");
		flag = HOME;
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		env = get_env(envl, "OLDPWD");
		flag = OLDPWD;
	}
	if (env)
		path = env->value;
	else
		path = argv[1];
	if (cd_path(path, envl, flag) == -1)
		return (put_cd_error(argv[0], path, flag));
	return (EXIT_SUCCESS);
}
