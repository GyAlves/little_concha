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

	cmd = shell->commands; // Pega os comandos da struct principal
	backup.in = -1;
	backup.out = -1;
	if (!process_all_heredocs(shell, cmd))
	{
		shell->exit_status = 1;
		return ;
	}
	if (cmd->is_piped)
	{
		// A contagem de argumentos aqui parece ser para um propósito específico.
		// A lógica principal de handle_pipes deve funcionar bem.
		shell->exit_status = handle_pipes(shell, cmd, shell->total_pipeln_cmd);
		return ;
	}
	if (is_builtin(cmd) && is_parent_builtin(cmd))
		shell->exit_status = handle_parent_bi_exec(shell, cmd);
	else
		exec_external_cmd(shell, cmd, NULL);
}

/* INICIA A PARSING  */

bool	parse_input(t_minishell *shell, t_token *tokens)
{
	int	cmd_pipe_count;

	if (!tokens || !tokens[0].content)
		return (true);
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

/*
int	parse_command(t_minishell *sh, t_command **cmd, t_token *args, char *prompt)
{
	int	cmd_pipe_count;

	if (!args || !args[0].content)
		return (0);
	cmd_pipe_count = count_pipes(args);
	sh->total_pipeln_cmd = cmd_pipe_count;
	if (!init_command_arr(cmd, cmd_pipe_count))
		return (0);
	if (cmd_pipe_count == 1)
	{
		if (!handle_single_cmd(cmd, args))
			return (0);
	}
	else
	{
		if (!handle_multi_cmd(cmd, args))
			return (0);
	}
	return (exec_command(sh, *cmd, prompt));
}*/

/* PARSER  */

int	handle_single_cmd(t_command **cmd, t_token *args)
{
	(*cmd)->is_piped = 0;
	if (!parse_single_cmd(*cmd, args, 0))
	{
		return (0);
	}
	return (1);
}

int	handle_multi_cmd(t_command **cmd, t_token *args)
{
	(*cmd)->is_piped = 1;
	if (!fill_cmd(args, *cmd))
	{
		//cleanup_command(*cmd);
		return (0);
	}
	return (1);
}
