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

int	handle_parent_bi_exec(t_minishell *sh, t_command *cmd)
{
	t_std_redir	backup;
	int			bi_exit_status;

	backup.in = dup(STDIN_FILENO);
	backup.out = dup(STDOUT_FILENO);

	if (!handle_redir_in_exc(sh, cmd))
	{
		restore_std_backup(&backup);
		return (sh->exit_status);
	}
	
	dispatch_builtin(sh, cmd);
	bi_exit_status = sh->exit_status;
	restore_std_backup(&backup);
	return (bi_exit_status);
}

static void	wait_for_child_process(t_minishell *sh, pid_t pid)
{
	int	status;
	int	term_sig;

	g_sig_status = 2;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		term_sig = WTERMSIG(status);
		if (term_sig == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (term_sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		sh->exit_status = 128 + term_sig;

	}
	g_sig_status = 0;
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
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		exec_cmd_in_child(sh, cmd);
		exit(127);
	}
	else
		wait_for_child_process(sh, pid);
	return (sh->exit_status);
}
