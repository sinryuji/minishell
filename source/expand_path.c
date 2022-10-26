/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:17:41 by jiwahn            #+#    #+#             */
/*   Updated: 2022/10/26 15:52:28 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>

#include "../libft/include/libft.h"
#include "../include/executor.h"
#include "../include/minishell.h"

static t_list	*make_pattern(char *text)
{
	int		i;
	char	flag;
	t_buf	buf;
	t_list	*pattern;

	i = 0;
	flag = 0;
	pattern = NULL;
	init_buf(&buf);
	while (text[i])
	{
		ctl_quote_flag(&flag, text[i]);
		if (!(flag & S_QUOTE + D_QUOTE) && text[i] == '*')
		{
			flush_pattern(&pattern, &buf);
			ft_lstadd_back(&pattern, ft_lstnew(ft_strdup("*")));
			while (text[i + 1] == '*')
				i++;
		}
		else
			append_to_buf(text[i], &buf);
		i++;
	}
	(flush_pattern(&pattern, &buf), free(buf.word), filter_pattern(&pattern));
	return (pattern);
}

static int	match_pattern(t_list *pattern, char *str)
{
	int		len;
	int		flag;

	flag = 0;
	while (pattern)
	{
		if (ft_strcmp(pattern->content, "*") == 0)
			flag = 1;
		else
		{
			len = ft_strlen(pattern->content);
			if (!match_pattern_compare(&str, pattern, flag, len))
				return (0);
			str += len;
			flag = 0;
		}
		pattern = pattern->next;
	}
	if (!flag && *str)
		return (0);
	return (1);
}

static t_list	*find_matches(t_list *pattern)
{
	DIR				*d;
	t_list			*matches;
	struct dirent	*dirent;

	matches = NULL;
	d = opendir(".");
	if (d == NULL)
		return (FALSE);
	while (1)
	{
		dirent = readdir(d);
		if (dirent == NULL)
			break ;
		if (ft_strncmp(dirent->d_name, ".", 1) == 0)
			continue ;
		if (match_pattern(pattern, dirent->d_name))
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(dirent->d_name)));
	}
	closedir(d);
	return (matches);
}

static t_token	*insert_matches(t_token *toks, t_list *matches)
{
	t_token	*new;
	t_token	*last;

	new = NULL;
	while (matches && *(char *)(matches->content))
	{
		tok_add_back(&new, get_new_token(WORD, matches->content));
		matches = matches->next;
	}
	if (new == NULL)
		return (toks);
	last = get_last_token(new);
	new->prev = toks->prev;
	last->next = toks->next;
	if (toks->prev)
		toks->prev->next = new;
	if (toks->next)
		toks->next->prev = get_last_token(new);
	free(toks->text);
	free(toks);
	return (last);
}

void	expand_pathname(t_tree *root)
{
	t_token	*toks;
	t_token	*save;
	t_list	*pattern;
	t_list	*matches;

	toks = root->toks;
	while (toks)
	{
		if (toks->type == WORD)
		{
			pattern = make_pattern(toks->text);
			matches = find_matches(pattern);
			toks = insert_matches(toks, matches);
		}
		if (toks->next == NULL)
			save = toks;
		toks = toks->next;
	}
	root->toks = get_first_token(save);
	ft_lstclear(&pattern, free);
	ft_lstclear(&matches, NULL);
}
