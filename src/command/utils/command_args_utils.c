/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:29 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 20:24:42 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int	count_command_args(char **args)
{
	int		counter;
	int		cmd_count;

	if (!args)
		return (0);
	counter = 0;
	cmd_count = 0;
	while (args[counter] && !is_pipe(args[counter]))
	{
		if (is_redir(args[counter]))
		{
			if (!args[counter + 1])
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

char	**copy_command_args(char **args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_pipe(args[i]))
			break ;
		if (is_redir(args[i]))
			i += 2;
		else
		{
			n_args[j] = ft_strdup(args[i]);
			if (!n_args[j])
			{
				free_matrix(n_args);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	n_args[j] = NULL;
	return (n_args);
}