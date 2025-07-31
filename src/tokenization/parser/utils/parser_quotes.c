/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:37:48 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 15:37:50 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
