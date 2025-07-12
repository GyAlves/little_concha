/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/12 16:33:41 by galves-a         ###   ########.fr       */
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
char        *cd_envar_home(t_minishell *sh);
int         change_curr_dir(t_minishell *sh, char *target);
int         handle_n_flag(char **args, int *index);
void        print_echo_args(t_minishell *sh, char **args, int index);
void        bi_export(t_minishell *sh, t_command *cmd);
void        bi_unset(t_minishell *sh, t_command *cmd);
void	    print_sorted_envar(t_minishell *sh);
void	    set_envar(t_minishell *sh, char *arg);
#endif