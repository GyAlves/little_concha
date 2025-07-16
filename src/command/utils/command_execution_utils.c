/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built-in.h"

int	exc_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
	int			status;
	t_std_redir	backup;

	backup.in = -1;
	backup.out = -1;
	if (!process_all_heredocs(sh, cmd))
		return (1);
	if (cmd->is_piped)
		return (handle_pipes(sh, cmd, count_command_args(cmd->args)));
	if (is_builtin(cmd) && is_parent_builtin(cmd))
	{
		if (!handle_redir_in_exc(sh, cmd, &backup))
		{
			restore_std_backup(&backup);
			return (sh->exit_status);
		}
		dispatch_builtin(sh, cmd, prompt);
		restore_std_backup(&backup);
		return (sh->exit_status);
	}
	else
	{
		exec_cmd(sh, cmd, prompt);
		status = sh->exit_status;
	}
	return (status);
}