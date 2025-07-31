/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:38:42 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 15:39:12 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_past_token(const char *input, int *i)
{
	bool	is_single;
	bool	is_double;

	if (is_operator(input[*i]))
	{
		if (input[*i] == '>' && input[*i + 1] == '>')
			(*i) += 2;
		else if (input[*i] == '<' && input[*i + 1] == '<')
			(*i) += 2;
		else
			(*i)++;
		return ;
	}
	is_single = false;
	is_double = false;
	while (input[*i] && (is_single || is_double \
		|| (input[*i] != ' ' && !is_operator(input[*i]))))
	{
		if (input[*i] == '\'' && !is_double)
			is_single = !is_single;
		else if (input[*i] == '"' && !is_single)
			is_double = !is_double;
		(*i)++;
	}
}

int	count_tokens(char *input)
{
	int	tokens_count;
	int	i;

	tokens_count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		tokens_count++;
		skip_past_token(input, &i);
	}
	return (tokens_count);
}
