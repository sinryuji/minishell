/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:00:41 by hyeongki          #+#    #+#             */
/*   Updated: 2022/04/25 13:09:53 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	get_word_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	if (!*s)
		return (0);
	if (*s != c)
		cnt++;
	s++;
	while (*s)
	{
		if (*s != c && *(s - 1) == c)
			cnt++;
		s++;
	}
	return (cnt);
}

static void	ret_free(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static int	split_str(char **ret, char const *s, char c)
{
	size_t	word_i;
	size_t	ret_i;

	ret_i = 0;
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		word_i = 0;
		while (*(s + word_i) && *(s + word_i) != c)
			word_i++;
		ret[ret_i] = ft_strndup(s, word_i);
		if (!ret[ret_i])
		{
			ret_free(ret);
			return (0);
		}
		s += word_i;
		ret_i++;
	}
	ret[ret_i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (get_word_cnt(s, c) + 1));
	if (!s || !ret)
		return (NULL);
	if (!split_str(ret, s, c))
		return (NULL);
	return (ret);
}
