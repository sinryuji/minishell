/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:33:35 by hyeongki          #+#    #+#             */
/*   Updated: 2022/06/01 00:38:36 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_itoa_base(long long n, int base)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = ft_nbrlen_base(n, base);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[0] = '-';
		n *= -1;
		i++;
	}
	ret[len] = '\0';
	while (--len >= i)
	{
		ret[len] = HEX_LOWER[n % base];
		n /= base;
	}
	return (ret);
}
