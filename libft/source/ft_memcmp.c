/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:26:36 by hyeongki          #+#    #+#             */
/*   Updated: 2022/04/13 12:20:43 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	if (n == 0)
		return (0);
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (i < n && c1[i] == c2[i])
		i++;
	if (i == n)
		i--;
	return (c1[i] - c2[i]);
}
