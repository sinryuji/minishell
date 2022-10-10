/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jiwahn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:06:33 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/10 13:53:08 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * main function for testing parser and scanner
 * */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "../include/parser.h"

void	print_toks(t_token *toks)
{
	while (toks)
	{
		printf("[%d]%s->", toks->type, toks->text);
		toks = toks->next;
	}
	printf("\n");
}

void	traverse_tree(t_tree *root)
{
	if (root)
	{
		traverse_tree(root->right);
		if (root->right == NULL && root->left == NULL)
		{
			printf("(%d): %s\n", root->type, root->toks->text);
			return ;
		}
		traverse_tree(root->left);
	}
}

void	leak_test(void)
{
	system("leaks a.out");
}

int main(int argc, char *argv[])
{
	t_token		*toks;
	t_tree		*root;
	char		*input;

	//leak check
	atexit(leak_test);

	//lexer
	toks = NULL;
	input = readline("input>> ");
	scanner(&toks, input);
	printf("\nscanner executed\n");
	print_toks(toks);

	//parse here
	root = get_new_node(0 & LEFT, LIST, toks);
	parser(toks, root);
	printf("\n\nparser executed\n");
	traverse_tree(root);
	free(input);
	//free tree
	return (0);
}
