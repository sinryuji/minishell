/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:25:51 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/05 17:59:31 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/scanner.h"
#include "../libft/libft.h"

void	err_exit(void)
{
	const char	*err = strerror(errno);
	write(STDERR_FILENO, err, ft_strlen(errno));
	exit(EXIT_FAILURE);
}

void	init_buffer(t_buffer *buffer)
{
	buffer->size = 0;
	word = (char *)malloc(sizoef(char) * BUF_SIZE);
	if (errno)
		err_exit();
}
