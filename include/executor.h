/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:20:56 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/25 17:36:40 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env.h"
# include "parser.h"

//syntax.c
int		check_syntax(t_tree *root, int ret);
int		is_redir(t_token *toks);

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
