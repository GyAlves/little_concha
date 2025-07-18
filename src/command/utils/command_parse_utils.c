/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:15:47 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/15 20:04:03 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_single_command(t_command *cmd, char **args, \
		int start, t_cmd_init *cmd_init)
{
	if (!cmd || !args || !cmd_init)
		return (false);
	cmd->is_piped = 0;
	cmd->redirections_count = 0;
	cmd_init->cmd_count = count_command_args(args + start);
	cmd_init->cmd_args = ft_calloc(cmd_init->cmd_count + 1, sizeof(char *));
	if (!cmd_init->cmd_args)
		return (false);
	return (true);
}

bool	parse_single_cmd(t_command *cmd, char **args, int start)
{
	t_cmd_init	cmd_init;

	if (!init_single_command(cmd, args, start, &cmd_init))
		return (false);
	if (!copy_command_args(args + start, cmd_init.cmd_args))
	{
		free_matrix(cmd_init.cmd_args);
		return (false);
	}
	if (!init_cmd_redirection(cmd, args + start))
	{
		free_matrix(cmd_init.cmd_args);
		return (false);
	}
	cmd->args = cmd_init.cmd_args;
	return (true);
}

int	init_cmd_redirection(t_command *cmd, char **args)
{
	cmd->redirections_count = count_redirs(args);
	cmd->redirects = ft_calloc(cmd->redirections_count + 1, sizeof(t_redirect));
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args))
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}
