/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/13 16:52:45 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../libft/include/libft.h"

t_tree	*get_new_node(int type, int flag, t_token *toks)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	node->type = type;
	node->flag = flag;
	node->toks = toks;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	parse_list(t_token **toks, t_tree *root)
{
	int		success;
	t_token	*tmp;

	success = 0;
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN) && \
				(!ft_strncmp((*toks)->text, "&&", 2) || \
				 !ft_strncmp((*toks)->text, "||", 2)))
		{
			success = 1;
			break ;
		}
		else if ((*toks)->type == OP && \
				(!ft_strncmp((*toks)->text, "(", 1) || \
				  !ft_strncmp((*toks)->text, ")", 1)))
			(root->flag) ^= PAREN;
		//*toks = (root->flag & LEFT) ? (*toks)->prev : (*toks)->next;
		if ((*toks)->prev == NULL)
			tmp = *toks;
		*toks = (*toks)->prev;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	if (!success)
	{
		*toks = tmp;
		root->type = PIPELINE;
		root->flag ^= LEFT;
	}
	else
		root->flag &= FOUND;
}

void	parse_pipeline(t_token **toks, t_tree *root)
{
	int		success;
	t_token	*origin;

	success = 0;
	origin = *toks;
	while (*toks)
	{
		if ((*toks)->type == OP && !(root->flag & PAREN) &&\
				!ft_strncmp((*toks)->text, "|", 1))
		{
			success = 1;
			break ;
		}
		else if ((*toks)->type == OP && \
				(!ft_strncmp((*toks)->text, "(", 1) || \
				  !ft_strncmp((*toks)->text, ")", 1)))
			(root->flag) ^= PAREN;
		*toks = (*toks)->next;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	if (!success)
	{
		*toks = origin;
		root->type = CMD;
	}
	else
		root->flag &= FOUND;
}

void	parse_cmd(t_token **toks, t_tree *root)
{
	int		subsh;
	t_token	*origin;

	origin = *toks;
	subsh = FALSE;
	while (*toks)
	{
		if ((*toks)->type == OP && \
			(!ft_strncmp((*toks)->text, "(", 1) || \
			  !ft_strncmp((*toks)->text, ")", 1)))
		{
			(root->flag) ^= PAREN;
			subsh = TRUE;
		}
		*toks = (*toks)->next;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	else if (subsh == TRUE)
		root->type = SUBSH;
	(root->flag) &= TERM;
	*toks = origin;
}

t_tree	*make_left_node(t_token *toks, t_tree *root)
{
	t_tree	*new;

	if (toks == NULL)
		return (NULL);
	toks->next = NULL;
	new = get_new_node(LIST, 0 & LEFT, toks);
	return (new);
}

t_tree	*make_right_node(t_token *toks, t_tree *root)
{
	t_tree	*new;

	if (toks == NULL)
		return (NULL);
	toks->prev = NULL;
	new = get_new_node(LIST, 0, toks);
	return (new);
}

void	make_root_node(t_token *toks, t_tree **root)
{
	if ((*root)->flag & FOUND)
	{
		if ((*root)->type == LIST)
			(*root)->type = CTLOP;
		if ((*root)->type == PIPELINE)
			(*root)->type = PIPE;
		toks->next = NULL;
		toks->prev = NULL;
		(*root)->toks = toks;
	}
} 

void	parser(t_token *toks, t_tree *root)
{
	t_token	*origin = toks;
	t_tree	*left = NULL;
	t_tree	*right = NULL;;

	if (toks == NULL || root == NULL)
		return ;
	if ((root->flag) & TERM)
		return ;
	if (root->type == LIST)
		parse_list(&toks, root);
	if (root->type == PIPELINE)
		parse_pipeline(&toks, root);
	if (root->type == CMD)
		parse_cmd(&toks, root);
	
	left = make_left_node(toks->prev, root);
	right = make_right_node(toks->next, root);
	make_root_node(toks, &root);
	root->left = left;
	root->right = right;
	parser(toks->next, root->right);
	if (toks->type == LIST)
		parser(toks->prev, root->left);
	else
		parser(get_first_token(toks), root->left);
}
