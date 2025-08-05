/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:47:49 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/05 15:38:56 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_mixed_content(char *content, t_minishell *shell)
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
		if (content[i] == '\'')
		{
			i++;
			while (content[i] && content[i] != '\'')
				i++;
			if (content[i] == '\'')
				i++;
			temp = ft_substr(content, start + 1, i - start - 2);
		}
		else
		{
			while (content[i] && content[i] != '\'')
				i++;
			temp = ft_substr(content, start, i - start);
			if (is_variable_expansion(temp))
			{
				char *expanded = expanded_variable(temp, shell);
				free(temp);
				temp = expanded;
			}
		}
		result = join_and_free(result, temp);
	}
	return (result);
}

char	*non_quoted_token(char *content, t_minishell *shell)
{
	if (ft_strchr(content, '\''))
		return (process_mixed_content(content, shell));
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

	if (!content)
		return (NULL);
	cleaned_content = strip_outer_quotes(content, ft_strlen(content), shell);
	if (!cleaned_content)
		return (NULL);
	return (expand_and_free(cleaned_content, shell));
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
