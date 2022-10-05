/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:11 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/05 17:53:46 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# define S_QUOTE  0x01 //1 on not closed
# define D_QUOTE  0x02 //1 on not closed
# define TOK_DET  0x04 //1 on not determined
# define TOK_TYPE 0x08 //1 on ops

# define BUF_SIZE 1024

enum e_token_type
{
	word = 0,
	op
};

typedef struct s_token
{
	int				type;
	char			*text;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_buffer
{
	int		size;
	char	*word;
}t_buffer;

//scanner.c
void	scanner(t_token **tokens, char *script);


#endif
