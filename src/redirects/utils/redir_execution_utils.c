/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_single_redir(t_redirect *redir, t_std_redir *backup)
{
	save_std_backup(backup, redir);
	if (!apply_redir(redir))
		return (0);
	return (1);
}

int	process_all_heredocs(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redirections_count)
	{
		if (cmd->redirects[i].type == HEREDOC)
		{
			if (!handle_heredoc(&cmd->redirects[i], sh))
			{
				sh->exit_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	handle_redir_in_exc(t_minishell \
	*sh, t_command *cmd, t_std_redir *backup)
{
	int	i;

	i = 0;
	while (i < cmd->redirections_count)
	{
		if (!process_single_redir(&cmd->redirects[i], backup))
		{
			sh->exit_status = 1;
			restore_std_backup(backup);
			return (0);
		}
		i++;
	}
	return (1);
}