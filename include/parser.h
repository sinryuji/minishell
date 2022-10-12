/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:32 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/11 16:13:02 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"

# define PAREN 0x01 // set subshell pair
# define LEFT  0x02 // to get left associativity
# define TERM  0x04 //terminate once it's on

enum e_type
{
	LIST,
	CTLOP,
	PIPELINE,
	PIPE,
	CMD,
	REDIR,
	SUBSH
};

typedef struct s_tree
{
	int				type;
	int				flag;
	t_token			*toks;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

//parser.c
void	parser(t_token *toks, t_tree *root);
t_tree	*get_new_node(int type, int flag, t_token *toks);
void	parse_list(t_token **toks, t_tree *root);
void	parse_pipe(t_token **toks, t_tree *root);
void	parse_cmd(t_token **toks, t_tree *root);

#endif
