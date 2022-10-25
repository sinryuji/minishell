/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:20:56 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 03:25:43 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "env.h"
# include "parser.h"
# include "../libft/include/libft.h"

typedef struct s_new_str
{
	char	*pre;
	char	*mid;
	char	*post;
}t_new_str;

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

//expand_env_utils.c
int	is_allowed(char c);
char	*get_env_val(t_env *env);
char	*strjoin_3way(char *pre, char *mid, char *post);

//split_field.c
void	split_field(t_tree *root);

//expand_path.c
void	expand_pathname(t_tree *root);

//expand_path_utils.c
void	flush_pattern(t_list **pattern, t_buf *buf);
void	filter_pattern(t_list **pattern);
int		match_pattern_compare(char **str, t_list *pattern, int flag, int len);

//remove_quote.c
void	quote_removal(t_tree *root);

#endif
