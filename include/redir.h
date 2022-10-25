/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:15:41 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 12:57:05 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "scanner.h"
# include <unistd.h>

# define TMP_FILE "./minishell_heredoc_tmp"

typedef struct s_redir
{
	char			*redir;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

typedef struct s_redir_list
{
	struct s_redir	*head;
	struct s_redir	*tail;
	int				tmp[2];
}	t_redir_list;

typedef struct s_heredoc
{
	char				*eof;
	struct s_heredoc	*prev;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_heredoc_list
{
	struct s_heredoc	*head;
	struct s_heredoc	*tail;
	int					tmp;
}	t_heredoc_list;

/* redir_01.c */
int			redir(t_redir_list *redirl);
int			heredoc(t_heredoc_list *heredocl);

/* redir_02.c */
t_redir		*new_redir(char *redir, char *file);
int			set_redir(t_redir_list **redirl, t_redir *redir);
void		free_redirl(t_redir_list **redirl);
void		free_redir(t_redir *redir);

/* redir_03.c */
t_heredoc	*new_heredoc(char *eof);
int			set_heredoc(t_heredoc_list **heredocl, t_heredoc *heredoc);
void		free_heredoc(t_heredoc *heredoc);
void		free_heredocl(t_heredoc_list **heredocl);

#endif
