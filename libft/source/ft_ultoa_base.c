/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:33:35 by hyeongki          #+#    #+#             */
/*   Updated: 2022/06/01 00:29:27 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_ultoa_base(unsigned long n, int base)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = ft_ullen_base(n, base);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (--len >= i)
	{
		ret[len] = HEX_LOWER[n % base];
		n /= base;
	}
	return (ret);
}
