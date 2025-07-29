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
