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

static char	*expand_envar(t_minishell *shell, char *key)
{
	char	*envar_entry;
	char	*val;

	envar_entry = find_envar(shell->envp, key);
	if (!envar_entry)
		return (ft_strdup(""));
	val = ft_strchr(envar_entry, '=');
	if (!val || *(val + 1) == '\0')
		return (ft_strdup(""));
	return (ft_strdup(val + 1));
}

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

static char	*handle_exit_status(t_minishell *shell)
{
	return (ft_itoa(shell->exit_status));
}

static char	*handle_variable(char *content, int *counter, t_minishell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *counter;
	while (content[*counter] && (isalnum(content[*counter])
			|| content[*counter] == '_'))
		(*counter)++;
	var_name = ft_substr(content, start, *counter - start);
	var_value = expand_envar(shell, var_name);
	free(var_name);
	return (var_value);
}

static char	*join_and_free(char *result, char *to_add)
{
	char	*temp;

	temp = ft_strjoin(result, to_add);
	free(result);
	free(to_add);
	return (temp);
}

char	*expanded_variable(char *content, t_minishell *shell)
{
	char	*result;
	char	*var_value;
	int		counter;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	counter = 0;
	while (content[counter])
	{
		if (content[counter] == '$')
		{
			counter++;
			if (content[counter] == '?')
			{
				var_value = handle_exit_status(shell);
				counter++;
			}
			else if (isalpha(content[counter]) || content[counter] == '_')
				var_value = handle_variable(content, &counter, shell);
			else
			{
				result = join_and_free(result, ft_strdup("$"));
				continue ;
			}
			result = join_and_free(result, var_value);
		}
		else
		{
			char	single_char[2];

			single_char[0] = content[counter];
			single_char[1] = '\0';
			result = join_and_free(result, ft_strdup(single_char));
			counter++;
		}
	}
	return (result);
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