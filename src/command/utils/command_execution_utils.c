/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/15 23:42:44 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parent_bi_exec(t_minishell *sh, t_command *cmd, \
			char *prompt, t_std_redir *backup)
{
	if (!handle_redir_in_exc(sh, cmd, backup))
	{
		restore_std_backup(backup);
		return (sh->exit_status);
	}
	dispatch_builtin(sh, cmd, prompt);
	restore_std_backup(backup);
	return (sh->exit_status);
}

int	exec_command(t_minishell *sh, t_command *cmd, char *prompt)
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
		return (handle_parent_bi_exec(sh, cmd, prompt, &backup));
	else
	{
		exec_external_cmd(sh, cmd, prompt);
		status = sh->exit_status;
	}
	return (status);
}

static void	wait_for_child_process(t_minishell *sh, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_status = 128 + WTERMSIG(status);
}

int	exec_external_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
	pid_t		pid;

	(void)prompt;
	if (cmd->is_piped || sh->total_pipeln_cmd > 1)
		return (handle_pipes(sh, cmd, sh->total_pipeln_cmd));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork failed!");
		sh->exit_status = 1;
		exit(1);
	}
	if (pid == 0)
	{
		exec_cmd_in_child(sh, cmd);
		exit(127);
	}
	else
		wait_for_child_process(sh, pid);
	return (sh->exit_status);
}
