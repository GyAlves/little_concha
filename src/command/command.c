/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:28:23 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 19:12:09 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_command(t_minishell *sh, t_command **cmd, char **args, char *prompt)
{
    int cmd_count;

    if (!args || !args[0])
        return 0;
    cmd_count = count_pipes(args);
    sh->total_pipeln_cmd = cmd_count;
    if (!init_command_arr(cmd, cmd_count))
        return (0);
    if (cmd_count == 1)
    {
        if (!handle_single_cmd(cmd, args))
            return (0);
    }
    else
    {
        if (!handle_multi_cmd(cmd, args))
            return (0);
    }
    return(exc_cmd(sh, *cmd, prompt));
}

int handle_single_cmd(t_command **cmd, char **args)
{
    (*cmd)->piped = 0;
    if (!parse_single_cmd(*cmd, args, 0))
    {
        free(*cmd);
        return 0;
    }
    return 1;
}

int handle_multi_cmd(t_command **cmd, char **args)
{
    (*cmd)->piped = 1;
    if (!fill_cmd(args, *cmd))
    {
        cleanup_cmd(*cmd);
        return 0;
    }
    return 1;
}

