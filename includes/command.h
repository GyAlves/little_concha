/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:54:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 19:35:54 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include "minishell.h"

/* COMMAND STRUCTURE  */
typedef struct s_command
{
    char			**args;        
    int				redirections_count;
    int				is_piped;
    t_redirect		*redirects;    
    t_pipe_data		*pipe;
} t_command;

/* Functions */
int	init_command(t_minishell *sh, t_command **cmd, char **args, char *prompt);
int	init_command_arr(t_command **cmd, int cmd_count);
int handle_single_cmd(t_command **cmd, char **args);
int handle_multi_cmd(t_command **cmd, char **args);
int	parse_single_cmd(t_command *cmd, char **args, int start);
int	count_command_args(char **args);
void cleanup_cmd(t_command *cmd);

#endif