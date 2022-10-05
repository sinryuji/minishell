/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:23:06 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/16 18:12:11 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	get_m_flag(char **str)
{
	int	ret;

	ret = 0;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			ret = 1;
		(*str)++;
	}
	if (**str == '0' && (*(*str + 1)) == 'x')
		(*str) += 2;
	return (ret);
}

int	ft_atoi_hex(char *str)
{
	unsigned int	ret;
	int				m_flag;

	ret = 0;
	m_flag = get_m_flag(&str);
	while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') \
		|| (*str >= 'a' && *str <= 'f'))
	{
		if (*str >= '0' && *str <= '9')
			ret = ret * 16 + (*str - '0');
		else if (*str >= 'A' && *str <= 'F')
			ret = ret * 16 + (*str - ('A' - 10));
		else
			ret = ret * 16 + (*str - ('a' - 10));
		str++;
	}
	if (m_flag)
		ret *= -1;
	return (ret);
}
