/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:29 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/13 14:53:39 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

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
	int				success;
	t_token	*origin;

	success = 0;
	origin = *toks;
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
		*toks = (*toks)->prev;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	if (!success)
	{
		*toks = origin;
		(*toks)->type = PIPELINE;
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
		(*toks)->type = CMD;
	}
	else
		root->flag &= FOUND;
}

void	parse_cmd(t_token **toks, t_tree *root)
{
	int		subsh;
	t_token	*origin;

	origin = *toks;
	subsh = 0;
	while (*toks)
	{
		if ((*toks)->type == OP && \
			(!ft_strncmp((*toks)->text, "(", 1) || \
			  !ft_strncmp((*toks)->text, ")", 1)))
			(root->flag) ^= PAREN;
		*toks = (*toks)->next;
	}
	if (root->flag & PAREN)
		err_exit("syntax err");
	(root->flag) &= TERM;
	*toks = origin;
}

t_tree	*make_left_node(t_token *toks, t_tree *root)
{

}

t_tree	*make_right_node(t_token *toks, t_tree *root)
{
}

void	make_root_node(t_token *toks, t_tree **root)
{

}

void	parser(t_token *toks, t_tree *root)
{
	t_token	*origin = toks;
	t_tree	*left = NULL;
	t_tree	*right = NULL;;

	if ((root->flag) & TERM)
		return ;
	if (toks->type == LIST)
		parse_list(&toks, root);
	if (toks->type == PIPELINE)
		parse_pipeline(&toks, root);
	if (toks->type == CMD)
		parse_cmd(&toks, root);

	left = make_left_node(toks, root);
	right = make_right_node(toks, root);
	make_root_node(toks, &root);
	root->left = left;
	root->right = right;
	//TODO - figure out whether it's token prev or next
	parser(toks->prev, root->right);
	parser(toks->next, root->left);
}
