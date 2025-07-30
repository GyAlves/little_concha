/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:15:47 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:47:29 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_cmd_args(t_command *cmd, t_token *start_token)
{
	int	arg_count;

	arg_count = count_command_args(start_token);
	if (arg_count == -1)
		return (false);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
		return (false);
	if (copy_command_args(start_token, cmd->args) == NULL)
	{
		free(cmd->args);
		cmd->args = NULL;
		return (false);
	}
	return (true);
}

bool	init_cmd_redirection(t_command *cmd, t_token *args)
{
	cmd->redirections_count = count_redirs(args);
	if (cmd->redirections_count > 0)
	{
		cmd->redirects = ft_calloc(cmd->redirections_count + 1, \
			sizeof(t_redirect));
		if (!cmd->redirects)
			return (false);
		if (!fill_redirs(cmd, args))
		{
			free(cmd->redirects);
			return (false);
		}
	}
	else
		cmd->redirects = NULL;
	return (true);
}

bool	parse_single_cmd(t_command *cmd, t_token *args, int start)
{
	if (!init_cmd_args(cmd, args + start))
		return (false);
	if (!init_cmd_redirection(cmd, args + start))
	{
		free_string_matrix(cmd->args);
		cmd->args = NULL;
		return (false);
	}
	return (true);
}

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
		return (0);
	return (1);
}

