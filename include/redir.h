/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:15:41 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/20 15:22:17 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "scanner.h"
# include <unistd.h>

typedef struct	s_redir
{
	char			*redir;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_redir_list
{
	struct s_redir	*head;
	struct s_redir	*tail;
}	t_redir_list;


/* redir_01.c */
int		is_redir(char *text);
int		redir(t_redir_list *redirl, pid_t pid);

/* redir_02.c */
t_redir	*new_redir(char *redir, char *file);
int		set_redir(t_redir_list **redirl, t_redir *redir);
void	free_redirl(t_redir_list **redirl);
void	free_redir(t_redir *redir);

#endif
