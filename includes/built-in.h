/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 19:00:41 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "minishell.h"

/* Functions */
int         is_builtin(t_command *cmd);
int	        dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt);
void	    bi_cd(t_minishell *sh, t_command *cmd);
void	    bi_echo(t_minishell *sh, t_command *cmd);
void	    bi_env(t_minishell *sh, t_command *cmd);
void	    bi_exit(t_minishell *sh, t_command *cmd, char *prompt);
void	    bi_pwd(t_minishell *sh);

#endif