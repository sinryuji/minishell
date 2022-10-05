/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:49:08 by hyeongki          #+#    #+#             */
/*   Updated: 2022/04/13 12:22:47 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (s1[end] && end >= start && ft_strchr(set, s1[end]))
		end--;
	ret = malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1 + start, end - start + 1);
	ret[end - start + 1] = 0;
	return (ret);
}
