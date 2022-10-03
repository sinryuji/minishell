/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:38:32 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/03 19:52:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum e_node_type
{
	log_expr,
	pipeline,
	subshell,
	command,
	redirect
};

typedef struct s_log_expr
{
	char	*op;
	int		left;
	int		right;
}t_log_expr;

typedef struct s_pipeline
{
	int		*cmds;
}t_pipeline;

typedef struct s_subshell
{
	int		type;
	int		*cmds;
}t_subshell;

typedef struct s_redirect
{
	char	*op;
	char	*file;
}t_redirect;

typedef struct s_command
{
	char	*cmd;
	int		prefix;
	int		suffix;
}t_command;
