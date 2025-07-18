/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_child_process_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:45:36 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 20:00:33 by galves-a         ###   ########.fr       */
/*   Updated: 2025/07/18 19:59:18 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_bi(t_minishell *sh, t_command *cmd)
{
	if (is_builtin(cmd) && !is_parent_builtin(cmd))
	{
		dispatch_builtin(sh, cmd, NULL);
		exit(sh->exit_status);
	}
}

static char	*get_n_val_cmd_path(t_command *cmd)
{
	char	*full_cmd_path;

	if (!cmd->args[0])
	{
		print_cmd_err(NULL, "commmand not found!");
		exit(127);
	}
	full_cmd_path = set_path(cmd->args[0]);
	if (!full_cmd_path)
	{
		print_cmd_err(cmd->args[0], "command not found");
		exit(127);
	}
	return (full_cmd_path);
}

void	exec_cmd_in_child(t_minishell *sh, t_command *cmd)
{
	char		*full_cmd_path;
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;
	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		exit (1);
	handle_child_bi(sh, cmd);
	full_cmd_path = get_n_val_cmd_path(cmd);
	execve(full_cmd_path, cmd->args, sh->envp);
	perror("minishell");
	if (full_cmd_path != cmd->args[0])
		free(full_cmd_path);
	exit(126);
}
