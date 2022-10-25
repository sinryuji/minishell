/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:11 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 17:38:22 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# define S_QUOTE  0x01 //1 when not closed
# define D_QUOTE  0x02 //1 when not closed

# define BUF_SIZE 1024
# define ERR_MSG  "syntax error"

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
int		scanner(t_token **tokens, char *script);
void	ctl_quote_flag(char *flag, char c);
int		is_op(char c);
int		is_delim(char c);
int		find_op(char *script);

//scanner_utils.c
void	err_exit(char *err);
void	init_buf(t_buf *buf);
void	realloc_buf(t_buf *buf);
void	append_to_buf(char c, t_buf *buf);
void	flush_buf(t_token **toks, t_buf *buf);

//token_utils.c
t_token	*get_new_token(int type, char *text);
void	tok_add_back(t_token **tokens, t_token *tok);
t_token	*get_last_token(t_token *toks);
t_token	*get_first_token(t_token *toks);

#endif
