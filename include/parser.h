/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:32 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/07 17:25:20 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"

enum e_type
{
	CTLOP,
	SUBSH,
	REDIR,
	PIPE,
	CMD
};

typedef struct s_tree
{
	int				type;
	t_token			*tok;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

//parser.c
void	parser(t_token toks, t_tree **root);

#endif
