/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:00:28 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 18:12:01 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input(t_minishell *shell, char **prompt)
{
	*prompt = readline(PROMPT);
	if (!*prompt)
    {
        shell->exit_status = 111;
        return (NULL);
    }
	if (!*prompt || **prompt == '\0')
		return (NULL);
	add_history(*prompt);
	return (lexer(*prompt));
}

static int	process_single_redir(t_redirect *redir, t_std_redir *backup)
{
	save_std_backup(backup, redir);
	if (!apply_redir(redir))
		return (0);
	return (1);
}

static int	process_all_heredocs(t_minishell *sh, t_command *cmd)
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