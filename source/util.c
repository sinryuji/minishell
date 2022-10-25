/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:38:16 by hyeongki          #+#    #+#             */
/*   Updated: 2022/10/25 21:20:26 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	get_toks_length(t_token *toks)
{
	int	ret;

	ret = 0;
	while (toks)
	{
		ret++;
		toks = toks->next;
	}
	return (ret);
}

void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("type : %d, text : %s\n", toks->type, toks->text);
		toks = toks->next;
	}
}

void	print_tree(t_tree *root)
{
	t_token	*origin;

	if (root == NULL)
		return ;
	print_tree(root->left);
	origin = root->toks;
	while (root->toks)
	{
		printf("%s ", root->toks->text);
		root->toks = root->toks->next;
	}
	root->toks = origin;
	printf("\n");
	print_tree(root->right);
}
