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
#include "utils.h"

int	count_command_args(token_t *args)
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

char	**copy_command_args(token_t *args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i].content)
	{
		if (is_pipe(args[i].content))
			break ;
		if (is_redir(args[i].content))
			i += 2;
		else
		{
			n_args[j] = ft_strdup(args[i].content);
			if (!n_args[j])
			{
				free_string_matrix(n_args);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	n_args[j] = NULL;
	return (n_args);
}
