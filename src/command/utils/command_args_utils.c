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

static int	handle_redirection(t_token *args, int i)
{
	char	*next_token_content;

	next_token_content = args[i + 1].content;
	if (next_token_content == NULL || is_pipe(next_token_content)
		|| is_redir(next_token_content))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (next_token_content == NULL)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(next_token_content, 2);
		ft_putstr_fd("`\n", 2);
		return (-1);
	}
	return (2);
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
	int	skip_count;

	i = 0;
	j = 0;
	while (args[i].content && !is_pipe(args[i].content))
	{
		if (is_redir(args[i].content))
		{
			skip_count = handle_redirection(args, i);
			if (skip_count == -1)
				return (false);
			i += skip_count;
		}
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
