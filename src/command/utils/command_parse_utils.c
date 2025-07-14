/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:15:47 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 19:45:34 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    init_single_command(t_command *cmd, char **args, int cmd_count, char **cmd_args)
{
    if (!cmd || !args)
	    return (false);
    cmd->piped = 0;
	cmd->redir_count = 0;
    cmd_count = count_cmd_args(args + start);
    cmd_args = ft_calloc(cmd_count + 1, sizeof(char *));
    if (!cmd_args)
	    return (false);
}

bool    parse_single_cmd(t_command *cmd, char **args, int start)
{
	int		cmd_count;
	char	**cmd_args;

    if (!init_single_command(&cmd, &args, cmd_count, &cmd_args))
        return (false);
	if (!cpy_cmd_args(args + start, cmd_args))
	{
		free_matrix(cmd_args);
		return (false);
	}
	if (!init_cmd_redir(cmd, args + start))
	{
		free_matrix(cmd_args);
		return (false);
	}
	cmd->args = cmd_args;
	return (true);
}