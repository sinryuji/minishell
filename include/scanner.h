/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:11 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/07 16:47:29 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# define S_QUOTE  0x01 //1 when not closed
# define D_QUOTE  0x02 //1 when not closed

# define BUF_SIZE 1024

enum e_token_type
{
	WORD = 0,
	OP
};

typedef struct s_token
{
	int				type;
	char			*text;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_buf
{
	int		size;
	char	*word;
}t_buf;

//scanner.c
void	scanner(t_token **tokens, char *script);
t_token	*get_new_token(int type, char *text);
int		is_op(char c);
int		is_delim(char c);
void	tok_add_back(t_token **tokens, t_token *new);

//scanner_utils.c
void	err_exit(char *err);
void	init_buf(t_buf *buf);
void	realloc_buf(t_buf *buf);
void	append_to_buf(char c, t_buf *buf);
int		find_op(char *script);
void	flush_buf(t_token **toks, t_buf *buf);

//token_utils.c

#endif
