/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/11 19:56:14 by galves-a         ###   ########.fr       */
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
static      char    *cd_envar_home(t_minishell *sh);
static      int change_curr_dir(t_minishell *sh, char *target);
static      int	handle_n_flag(char **args, int *index);
static      void	print_echo_args(t_minishell *sh, char **args, int index);

#endif