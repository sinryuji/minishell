/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:28:08 by hyeongki          #+#    #+#             */
/*   Updated: 2022/08/18 19:50:02 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

double	ft_pow(double x, double y)
{
	double	ret;

	ret = 1;
	if (y < 0)
	{
		while (y++ < 0)
			ret *= x;
		ret = 1 / ret;
	}
	else
	{
		while (y--)
			ret *= x;
	}
	return (ret);
}
