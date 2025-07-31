/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:01:03 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:16:50 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input, t_minishell *shell)
{
	t_token	*tokens;
	int		tokens_count;
	int		input_counter;
	int		token_index;

	tokens_count = count_tokens(input);
	shell->tokens_count = tokens_count;
	tokens = malloc(sizeof(t_token) * (tokens_count + 1));
	if (!tokens)
		return (NULL);
	input_counter = 0;
	token_index = 0;
	while (input[input_counter])
	{
		while (input[input_counter] && input[input_counter] == ' ')
			input_counter++;
		if (!input[input_counter])
			break ;
		tokens[token_index] = fill_token(input, &input_counter);
		token_index++;
	}
	tokens[tokens_count] = (t_token){NULL, false, false};
	int i = 0;
	while (tokens[i].content)
	{
		printf("%i : [%s]\n", i, tokens[i].content);
		i++;
	}
	return (tokens);
}
