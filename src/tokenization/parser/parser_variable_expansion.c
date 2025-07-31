/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variable_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:30:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/25 14:30:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

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

static char	*handle_dollar_sign(char *content, int *ctr, t_minishell *sh, \
								char *res)
{
	char	*var_value;

	(*ctr)++;
	if (content[*ctr] == '?')
	{
		var_value = handle_exit_status(sh);
		(*ctr)++;
	}
	else if (ft_isalpha(content[*ctr]) || content[*ctr] == '_')
		var_value = handle_variable(content, ctr, sh);
	else
		return (join_and_free(res, ft_strdup("$")));
	return (join_and_free(res, var_value));
}

static char	*append_char(char *res, char c)
{
	char	single_char[2];

	single_char[0] = c;
	single_char[1] = '\0';
	return (join_and_free(res, ft_strdup(single_char)));
}

char	*expanded_variable(char *content, t_minishell *shell)
{
	char	*result;
	int		counter;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	counter = 0;
	while (content[counter])
	{
		if (content[counter] == '$')
			result = handle_dollar_sign(content, &counter, shell, result);
		else
		{
			result = append_char(result, content[counter]);
			counter++;
		}
	}
	return (result);
}
