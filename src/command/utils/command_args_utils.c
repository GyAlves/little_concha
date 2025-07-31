/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:29 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 20:00:18 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_command_args(t_token *args)
{
	int		counter;
	int		cmd_count;

	if (!args)
		return (0);
	counter = 0;
	cmd_count = 0;
	while (args[counter].content && !is_pipe(args[counter].content))
	{
		if (is_redir(args[counter].content))
		{
			if (!args[counter + 1].content)
				return (cmd_count);
			counter += 2;
		}
		else
		{
			cmd_count++;
			counter++;
		}
	}
	return (cmd_count);
}

bool	validate_tokens(t_minishell *shell, t_token *tokens)
{
	if (!validate_first_token(shell, tokens))
		return (false);
	return (validate_token_sequence(shell, tokens));
}

static int	copy_argument(char **n_args, int j, const char *content)
{
	n_args[j] = ft_strdup(content);
	if (!n_args[j])
	{
		free_string_matrix(n_args);
		return (0);
	}
	return (1);
}

static bool	iterate_and_copy_args(t_token *args, char **n_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i].content && !is_pipe(args[i].content))
	{
		if (is_redir(args[i].content))
			i += 2;
		else
		{
			if (!copy_argument(n_args, j, args[i].content))
				return (false);
			i++;
			j++;
		}
	}
	n_args[j] = NULL;
	return (true);
}

char	**copy_command_args(t_token *args, char **n_args)
{
	if (!args || !n_args)
		return (NULL);
	if (!iterate_and_copy_args(args, n_args))
		return (NULL);
	return (n_args);
}
