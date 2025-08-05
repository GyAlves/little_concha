/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:38:03 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 15:38:05 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_quoted_segment(const char *content, int *i, \
		int start, t_minishell *shell)
{
	char	*temp;
	char	*expanded;

	(*i)++;
	while (content[*i] && content[*i] != '"')
		(*i)++;
	if (content[*i] == '"')
		(*i)++;
	temp = ft_substr(content, start + 1, *i - start - 2);
	if (is_variable_expansion(temp))
	{
		expanded = expanded_variable(temp, shell);
		free(temp);
		temp = expanded;
	}
	return (temp);
}

char	*process_unquoted_segment(const char *content, int *i, \
		int start, t_minishell *shell)
{
	char	*temp;
	char	*expanded;

	while (content[*i] && content[*i] != '"')
		(*i)++;
	temp = ft_substr(content, start, *i - start);
	if (is_variable_expansion(temp))
	{
		expanded = expanded_variable(temp, shell);
		free(temp);
		temp = expanded;
	}
	return (temp);
}

char	*strip_outer_quotes(char *content, int len, t_minishell *shell)
{
	char	*cleaned_content;
	char	*mixed_processed;

	if (len >= 2 && content[0] == '"' && content[len - 1] == '"')
	{
		cleaned_content = ft_substr(content, 1, len - 2);
		if (!cleaned_content)
			return (NULL);
		if (ft_strchr(cleaned_content, '"'))
		{
			mixed_processed = process_mixed_quotes(cleaned_content, shell);
			free(cleaned_content);
			return (mixed_processed);
		}
		return (cleaned_content);
	}
	if (ft_strchr(content, '"'))
		return (process_mixed_quotes(content, shell));
	return (ft_strdup(content));
}

char	*expand_and_free(char *content_to_expand, t_minishell *shell)
{
	char	*expanded_content;

	if (is_variable_expansion(content_to_expand))
	{
		expanded_content = expanded_variable(content_to_expand, shell);
		free(content_to_expand);
		return (expanded_content);
	}
	return (content_to_expand);
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
			temp = process_quoted_segment(content, &i, start, shell);
		else
			temp = process_unquoted_segment(content, &i, start, shell);
		result = join_and_free(result, temp);
	}
	return (result);
}
