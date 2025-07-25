/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/25 17:39:17 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_parser(t_token *tokens, t_minishell *shell)
{
	char	**args;
	int		counter;

	counter = 0;
	args = malloc(sizeof(char *) * (shell->tokens_count + 1));
	if (!args)
		return (NULL);
	while (tokens[counter].content != NULL)
	{
		if (tokens[counter].was_single)
			args[counter] = single_quoted_token(tokens[counter].content);
		else if (tokens[counter].was_double)
			args[counter] = double_quoted_token(tokens[counter].content,
					shell);
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

char	*process_mixed_quotes(char *content, t_minishell *shell)
{
	char	*result;
	char	*temp;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (content[i])
	{
		start = i;
		if (content[i] == '"')
		{
			i++;
			while (content[i] && content[i] != '"')
				i++;
			if (content[i] == '"')
				i++;
			temp = ft_substr(content, start + 1, i - start - 2);
			if (is_variable_expansion(temp))
			{
				char *expanded = expanded_variable(temp, shell);
				free(temp);
				temp = expanded;
			}
		}
		else
		{
			while (content[i] && content[i] != '"')
				i++;
			temp = ft_substr(content, start, i - start);
			if (is_variable_expansion(temp))
			{
				char *expanded = expanded_variable(temp, shell);
				free(temp);
				temp = expanded;
			}
		}
		char *new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
	}
	return (result);
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
		cleaned_content = ft_substr(content, start, end - start);
		if (!cleaned_content)
			return (NULL);
		if (ft_strchr(cleaned_content, '"'))
		{
			expanded_content = process_mixed_quotes(cleaned_content, shell);
			free(cleaned_content);
			return (expanded_content);
		}
	}
	else
	{
		cleaned_content = ft_strdup(content);
		if (!cleaned_content)
			return (NULL);
	}
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