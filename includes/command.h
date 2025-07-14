/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:54:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/13 23:37:44 by gyasminalve      ###   ########.fr       */
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
int	setup_command(t_minishell *sh, t_command **cmd, char **args, char *prompt);

#endif