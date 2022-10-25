/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:32 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 21:34:04 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"

# define PAREN 0x01 // set subshell pair
# define FOUND 0x02 // terminate once it's on

# define ROOT	0
# define LEFT	1
# define RIGHT	2

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
	struct s_tree	*parent;
}t_tree;

//parser.c
int		parser(t_tree *root, int ret);
int		parse_list(t_tree *root);
int		parse_pipeline(t_tree *root);
int		parse_cmd(t_tree *root);

//parse_list.c
int		parse_list(t_tree *root);

//parse_cmd.c
int		parse_cmd(t_tree *root);

//parse_pipeline.c
int		parse_pipeline(t_tree *root);

//tree_utils_01.c
t_tree	*get_new_node(int type, int flag, t_token *toks, t_tree *parent);
t_tree	*make_right_node(t_tree *root);
t_tree	*make_left_node(t_tree *root);
void	make_root_node(t_tree **root);
int		who_am_i(t_tree *root);

/* tree_utils_02.c */
t_tree	*get_sibilng_node(t_tree *root);

#endif
