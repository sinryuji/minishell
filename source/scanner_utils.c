/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:25:51 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/10 13:11:21 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/scanner.h"
#include "../libft/include/libft.h"

void	err_exit(char *err)
{
	if (errno)
		err = strerror(errno);
	write(STDERR_FILENO, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

#include <stdio.h>
void	init_buf(t_buf *buf)
{
	buf->size = 0;
	buf->word = (char *)malloc(sizeof(char) * BUF_SIZE);
	if (!buf->word)
		err_exit(NULL);
}

void	realloc_buf(t_buf *buf)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * buf->size * 2);
	if (!word)
		err_exit(NULL);
	ft_memmove(word, buf->word, buf->size);
	free(buf->word);
	buf->word = word;
}

void	append_to_buf(char c, t_buf *buf)
{
	if (buf->size != 0 && (buf->size % BUF_SIZE == 0))
		realloc_buf(buf);
	buf->word[buf->size] = c;
	(buf->size)++;
} 

void	flush_buf(t_token **toks, t_buf *buf)
{
	if (buf->size != 0)
	{
		tok_add_back(toks, get_new_token(WORD, ft_strndup(buf->word, buf->size)));
		free(buf->word);
		init_buf(buf);
	}
}
