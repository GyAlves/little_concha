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

void	expand_tokens(t_minishell *shell, t_token *tokens)
{
	int		i;
	char	*content_original;

	i = 0;
	if (!tokens)
		return;
	while (tokens[i].content)
	{
		content_original = tokens[i].content;
		if (tokens[i].was_single)
			tokens[i].content = single_quoted_token(content_original);
		else if (tokens[i].was_double)
			tokens[i].content = double_quoted_token(content_original, shell);
		else
			tokens[i].content = non_quoted_token(content_original, shell);
		free(content_original);
		if (!tokens[i].content)
		{
			// Em caso de erro, uma abordagem robusta seria limpar tudo e sair.
			// Por enquanto, vamos parar o processo de expansão.
			return ;
		}
		i++;
	}
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
	char	*expanded;
	char	*new_result;

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
				expanded = expanded_variable(temp, shell);
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
				expanded = expanded_variable(temp, shell);
				free(temp);
				temp = expanded;
			}
		}
		new_result = ft_strjoin(result, temp);
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
