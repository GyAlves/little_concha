/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/25 14:21:12 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

char	**tokens_parser(token_t *tokens, t_minishell *shell)
{
	char	**args;
	int		counter;

	counter = 0;
	args = malloc(sizeof(char *) * (shell->tokens_count + 1));
	if (!args)
		return (NULL);
	while (tokens[counter].content != NULL)
	{
		if (tokens[counter].was_double)
			args[counter] = double_quoted_token(tokens[counter].content,
					shell);
		else if (tokens[counter].was_single)
			args[counter] = single_quoted_token(tokens[counter].content);
		else
			args[counter] = non_quoted_token(tokens[counter].content,
					shell);
		counter++;
	}
	args[shell->tokens_count] = NULL;
	return (args);
}

char	*non_quoted_token(char *content, t_minishell *shell)
{
	if (is_variable_expansion(content))
		return (expanded_variable(content, shell));
	return (ft_strdup(content));
}

char	*single_quoted_token(char *content)
{
	int	len;
	int	start;
	int	end;

	if (!content)
		return (NULL);
	len = ft_strlen(content);
	start = 0;
	end = len;
	if (len >= 2 && content[0] == '\'' && content[len - 1] == '\'')
	{
		start = 1;
		end = len - 1;
	}
	if (end <= start)
		return (ft_strdup(""));
	return (ft_substr(content, start, end - start));
}

char	*double_quoted_token(char *content, t_minishell *shell)
{
	char	*cleaned_content;
	char	*expanded_content;
	int		len;
	int		start;
	int		end;

	if (!content)
		return (NULL);
	len = ft_strlen(content);
	start = 0;
	end = len;
	if (len >= 2 && content[0] == '"' && content[len - 1] == '"')
	{
		start = 1;
		end = len - 1;
	}
	if (end <= start)
		return (ft_strdup(""));
	cleaned_content = ft_substr(content, start, end - start);
	if (!cleaned_content)
		return (NULL);
	if (is_variable_expansion(cleaned_content))
	{
		expanded_content = expanded_variable(cleaned_content, shell);
		free(cleaned_content);
		return (expanded_content);
	}
	return (cleaned_content);
}

bool	is_variable_expansion(char *content)
{
	int		counter;
	char	current;

	counter = 0;
	while (content[counter] != '\0')
	{
		current = content[counter];
		if (current == '$')
		{
			if (content[counter + 1] == '?')
				return (true);
			else if (isalpha(content[counter + 1])
				|| content[counter + 1] == '_')
				return (true);
			else if (content[counter + 1] != '\0')
				return (false);
		}
		counter++;
	}
	return (false);
}