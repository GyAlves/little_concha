/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:15:47 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 20:30:15 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    init_single_command(t_command *cmd, char **args, int start, t_cmd_init *cmd_init)
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

bool    parse_single_cmd(t_command *cmd, char **args, int start) //inicializa a struct para um unico comando, conta argumentos e redirs
{
    t_cmd_init cmd_init;

    if (!init_single_command(cmd, args, start, &cmd_init))
        return (false);
    if (!copy_command_args(args + start, cmd_init.cmd_args)) //copia os argumentos do cmd(exceto pipes e redirs)
    {
        free_matrix(cmd_init.cmd_args);
        return (false);
    }
    if (!init_cmd_redir(cmd, args + start))
    {
        free_matrix(cmd_init.cmd_args);
        return (false);
    }
    cmd->args = cmd_init.cmd_args;
    return (true);
}

int	init_cmd_redir(t_command *cmd, char **args) //inicializa a struct de redir 
{
	cmd->redirections_count = count_redirs(args); //adiciona a contagem de redirs a struct
	cmd->redirects = ft_calloc(cmd->redirections_count + 1, sizeof(t_redirect)); //aloca memoria para a struct de redir
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args)) //confere os argumentos passados 
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}