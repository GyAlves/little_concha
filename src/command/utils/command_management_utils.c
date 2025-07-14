/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_management_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:31:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 19:32:56 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command_arr(t_command **cmd, int cmd_count)
{
	*cmd = ft_calloc(cmd_count, sizeof(t_command));
	if (!*cmd)
		return (0);
	return (1);
}

void cleanup_cmd(t_command *cmd)
{
    free_cmd_struct(cmd);
    free(cmd);
}

int	count_command_args(char **args)
{
	int		counter;
	int		count;

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