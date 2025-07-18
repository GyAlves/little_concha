/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:28:23 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/15 19:56:26 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_command(t_command **cmd, t_minishell *shell, \
		char **prompt, char ***args)
{
	int	counter;

	*cmd = NULL;
	shell->exit_status = init_command(shell, cmd, *args, *prompt);
	if (*cmd)
	{
		counter = 0;
		while (counter < shell->total_pipeln_cmd)
		{
			free_cmd_struct(&(*cmd)[counter]);
			counter++;
		}
		free(*cmd);
		*cmd = NULL;
	}
}

int	init_command(t_minishell *sh, t_command **cmd, char **args, char *prompt)
{
	int	cmd_pipe_count;

	if (!args || !args[0])
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
}

int	handle_single_cmd(t_command **cmd, char **args)
{
	(*cmd)->is_piped = 0;
	if (!parse_single_cmd(*cmd, args, 0))
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

int	handle_multi_cmd(t_command **cmd, char **args)
{
	(*cmd)->is_piped = 1;
	if (!fill_cmd(args, *cmd))
	{
		cleanup_command(*cmd);
		return (0);
	}
	return (1);
}
