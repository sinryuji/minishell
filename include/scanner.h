/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:11 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/04 21:51:41 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

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

#endif
