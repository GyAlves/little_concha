/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:28:23 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/22 19:49:18 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_minishell *shell)
{
	t_command	*cmd;
	t_std_redir	backup;

	cmd = shell->commands;
	backup.in = -1;
	backup.out = -1;
	if (!process_all_heredocs(shell, cmd))
	{
		shell->exit_status = 1;
		return ;
	}
	if (cmd->is_piped)
	{
		shell->exit_status = handle_pipes(shell, cmd, shell->total_pipeln_cmd);
		return ;
	}
	if (is_builtin(cmd) && is_parent_builtin(cmd))
		shell->exit_status = handle_parent_bi_exec(shell, cmd);
	else
		exec_external_cmd(shell, cmd, NULL);
}


bool	parse_input(t_minishell *shell, t_token *tokens)
{
	int	cmd_pipe_count;

	if (!tokens || !tokens[0].content)
		return (true);
	if (!validate_tokens(shell, tokens))
		return (false);
	cmd_pipe_count = count_pipes(tokens);
	shell->total_pipeln_cmd = cmd_pipe_count;
	if (!init_command_arr(&shell->commands, cmd_pipe_count))
		return (false);
	if (cmd_pipe_count == 1)
	{
		if (!handle_single_cmd(&shell->commands, tokens))
			return (false);
	}
	else
	{
		if (!handle_multi_cmd(&shell->commands, tokens))
			return (false);
	}
	return (true);
}
