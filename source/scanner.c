/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:05:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/05 14:20:58 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../include/scanner.h"

t_token	*get_new_token(int type, char *text)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = type;
	new_token->text = ft_strdup(text);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	tok_add_back(t_token **tokens, t_token *new)
{
	t_token	*p;

	p = *tokens;
	if (new == NULL)
		return ;
	if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = p;
}


/*
 * (char *)srcipt should end with a null char
 * */
void	scanner(t_token **tokens, char *script)
{
	int			i;
	char		c;
	char		flag;
	t_buffer	buffer;

	flag = 0;
	i = 0;
	while (1)
	{
		c = script[i];
	}
}

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
void	print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("[%d]%s->", tokens->type, tokens->text);
		tokens = tokens->next;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	t_token	*tokens;
	char	*input;

	tokens = NULL;
	input = readline("input>> ");
	scanner(&tokens, input, deli);
	print_tokens(tokens);
	free(input);
}
