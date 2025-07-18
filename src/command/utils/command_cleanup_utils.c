/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cleanup_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_struct(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
		free_matrix(cmd->args);
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
