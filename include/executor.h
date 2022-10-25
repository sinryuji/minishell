/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:20:56 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 22:17:16 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env.h"
# include "parser.h"

//syntax.c
int		check_syntax(t_tree *root, int ret);
int		is_redir(t_token *toks);

//syntax_check_lr.c
int		check_left_node(t_tree *root);
int		check_right_node(t_tree *root);

//syntax_check_node.c
int		check_node(t_tree *root);

//expander.c
void	expand(t_tree *root, t_env_list *envl);

//expand_env.c
void	expand_env(t_tree *root, t_env_list *envl);

//split_field.c
void	split_field(t_tree *root);

//expand_path.c
void	expand_pathname(t_tree *root);

//remove_quote.c
void	quote_removal(t_tree *root);

#endif
