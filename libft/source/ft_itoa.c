/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:44:05 by hyeongki          #+#    #+#             */
/*   Updated: 2022/04/13 12:18:50 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	get_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	get_div(int len)
{
	int	i;

	i = 1;
	if (len == 1)
		return (i);
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	return (i);
}

static void	do_itoa(char *ret, int n, int len)
{
	int	div;
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		ret[0] = '-';
		i++;
		len--;
	}
	div = get_div(len);
	while (div > 0)
	{
		ret[i] = n / div + '0';
		n -= n / div * div;
		div /= 10;
		i++;
	}
	ret[i] = 0;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_nbrlen(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	do_itoa(ret, n, len);
	return (ret);
}
