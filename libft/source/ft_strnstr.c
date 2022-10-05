/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:49:56 by hyeongki          #+#    #+#             */
/*   Updated: 2022/04/13 12:22:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	check(const char *hs, const char *nd, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (nd[j])
	{
		if (hs[i] != nd[j])
			return (0);
		j++;
		i++;
	}
	if (i > len)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{	
	size_t	i;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0] && check(haystack, needle, i, len))
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
