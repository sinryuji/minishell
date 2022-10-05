/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:11 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/04 20:25:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

enum e_type
{
	word = 0,
	op,
};

typedef struct s_token
{
	int		type;
	size_t	size;
	char	*text;
}t_token;



#endif
