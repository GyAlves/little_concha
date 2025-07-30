/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_management_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:31:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/15 19:56:27 by galves-a         ###   ########.fr       */
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

void	cleanup_command(t_command *cmd)
{
	free_cmd_struct(cmd);
	free(cmd);
}

void	free_cmd_struct(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
		free_string_matrix(cmd->args);
	if (cmd->redirects)
	{
		i = 0;
		while (i < cmd->redirections_count)
		{
			if (cmd->redirects[i].filename)
			{
				if (cmd->redirects[i].type == HEREDOC)
					unlink(cmd->redirects[i].filename);
				free(cmd->redirects[i].filename);
			}
			i++;
		}
		free(cmd->redirects);
	}
}
