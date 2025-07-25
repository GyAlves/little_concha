/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:16:18 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/22 19:41:09 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static token_t	*convert_strings_to_tokens(char **strings)
{
	token_t	*tokens;
	int		count;
	int		i;

	if (!strings)
		return (NULL);
	
	count = 0;
	while (strings[count])
		count++;
	
	tokens = malloc(sizeof(token_t) * (count + 1));
	if (!tokens)
		return (NULL);
	
	i = 0;
	while (i < count)
	{
		tokens[i].content = ft_strdup(strings[i]);
		tokens[i].was_double = false;
		tokens[i].was_single = false;
		if (!tokens[i].content)
		{
			while (i-- > 0)
				free(tokens[i].content);
			free(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[count].content = NULL;
	tokens[count].was_double = false;
	tokens[count].was_single = false;
	
	return (tokens);
}

bool	setup_prompt(t_minishell *shell, char **prompt, token_t **args)
{	
	char **processed_args = read_input(shell, prompt);
	
	if (!processed_args)
	{
		if (*prompt)
		{
			free(*prompt);
			*prompt = NULL;
		}
		return (false);
	}
	
	*args = convert_strings_to_tokens(processed_args);
	free_string_matrix(processed_args);
	
	if (!*args)
	{
		if (*prompt)
		{
			free(*prompt);
			*prompt = NULL;
		}
		return (false);
	}
	
	return (true);
}
