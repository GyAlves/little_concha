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

int	exec_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
	int			status;
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
	if (pid == 0) //filhote
	{
		exec_child(sh, cmd);
		exit (127);
	}
	else //papai
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			sh->exit_status = 128 + WTERMSIG(status);
	}
	return (sh->exit_status);
}

void	exec_child(t_minishell *sh, t_command *cmd) //
{
	char		*full_cmd_path;
	t_std_redir	child_redir_backup;

	child_redir_backup.in = -1;
	child_redir_backup.out = -1;

	if (!handle_redir_in_exc(sh, cmd, &child_redir_backup))
		exit (1);
	if (is_builtin(cmd) && !is_parent_builtin(cmd))
	{
		dispatch_builtin(sh,cmd, NULL);
		exit(sh->exit_status);
	}
	if (!cmd->args[0])
	{
		print_cmd_err(NULL, "commmand not found");
		exit(127);
	}
	full_cmd_path = set_path(cmd->args[0]);
	if (!full_cmd_path)
	{
		print_cmd_err(cmd->args[0], "command not found");
		exit(127);
	}
	execve(full_cmd_path, cmd->args, sh->envp);
	perror("minishell");
	if (full_cmd_path != cmd->args[0])
		free(full_cmd_path);
	exit (126);
}