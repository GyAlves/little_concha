/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fill_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:39:48 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 15:39:49 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_fill_quote_state(char c, t_token_temp *token)
{
	if (c == '\'' && !token->in_double_temp)
	{
		token->in_single_temp = !token->in_single_temp;
		token->was_single_temp = true;
	}
	else if (c == '"' && !token->in_single_temp)
	{
		token->in_double_temp = !token->in_double_temp;
		token->was_double_temp = true;
	}
}

static t_token	fill_operator_token(char *input, int *pos)
{
	int		start;
	char	*content;

	start = *pos;
	if ((input[start] == '>' && input[start + 1] == '>')
		|| (input[start] == '<' && input[start + 1] == '<'))
		*pos += 2;
	else
		(*pos)++;
	content = ft_substr(input, start, *pos - start);
	return ((t_token){content, false, false, true});
}

static t_token	fill_word_token(char *input, int *pos)
{
	t_token_temp	token;

	token.start_temp = *pos;
	token.in_single_temp = false;
	token.in_double_temp = false;
	token.was_single_temp = false;
	token.was_double_temp = false;
	while (input[*pos] && (token.in_single_temp || token.in_double_temp
			|| (input[*pos] != ' ' && !is_operator(input[*pos]))))
	{
		update_fill_quote_state(input[*pos], &token);
		(*pos)++;
	}
	token.content_temp = ft_substr(input, token.start_temp, *pos
			- token.start_temp);
	if (!token.content_temp)
		return ((t_token){NULL, false, false, false});
	if (token.was_single_temp && (token.start_temp == 0 || 
		token.content_temp[0] != '\'' || 
		token.content_temp[ft_strlen(token.content_temp) - 1] != '\''))
		return ((t_token){token.content_temp, false, false, false});
	return ((t_token){token.content_temp, token.was_double_temp,
		token.was_single_temp, false});
}

t_token	fill_token(char *input, int *pos)
{
	if (is_operator(input[*pos]))
		return (fill_operator_token(input, pos));
	else
		return (fill_word_token(input, pos));
}
