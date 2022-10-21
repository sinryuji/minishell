/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:32 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/19 21:42:58 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"

# define PAREN 0x01 // set subshell pair
# define FOUND 0x02 // terminate once it's on

enum e_type
{
	LIST,
	CTLOP,
	PIPELINE,
	PIPE,
	CMD,
	SUBSH
};

typedef struct s_tree
{
	int				type;
	char			flag;
	t_token			*toks;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

//parser.c
void	parser(t_tree *root);
void	parse_list(t_tree *root);
void	parse_pipeline(t_tree *root);
void	parse_cmd(t_tree *root);

//tree_utils.c
t_tree	*get_new_node(int type, int flag, t_token *toks);
t_tree	*make_right_node(t_tree *root);
t_tree	*make_left_node(t_tree *root);
void	make_root_node(t_tree **root);

#endif
