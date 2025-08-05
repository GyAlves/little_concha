/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:09 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/05 18:22:10 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

char	*join_and_free(char *result, char *to_add)
{
	char	*temp;

	temp = ft_strjoin(result, to_add);
	free(result);
	free(to_add);
	return (temp);
}

static char	*handle_single_quoted(const char *content, int *counter)
{
	int		start;
	char	*ret;

	start = *counter;
	(*counter)++;
	while (content[*counter] && content[*counter] != '\'')
		(*counter)++;
	if (content[*counter] == '\'')
		(*counter)++;
	ret = ft_substr(content, start + 1, *counter - start - 2);
	return (ret);
}

static char	*handle_non_quoted(const char *content, \
			int *counter, t_minishell *shell)
{
	int		start;
	char	*temp;
	char	*expanded;

	start = *counter;
	while (content[*counter] && content[*counter] != '\'')
		(*counter)++;
	temp = ft_substr(content, start, *counter - start);
	if (is_variable_expansion(temp))
	{
		expanded = expanded_variable(temp, shell);
		free(temp);
		temp = expanded;
	}
	return (temp);
}

char	*process_mixed_content(char *content, t_minishell *shell)
{
	char	*result;
	char	*temp;
	int		counter;

	result = ft_strdup("");
	counter = 0;
	while (content[counter])
	{
		if (content[counter] == '\'')
			temp = handle_single_quoted(content, &counter);
		else
			temp = handle_non_quoted(content, &counter, shell);
		result = join_and_free(result, temp);
	}
	return (result);
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
