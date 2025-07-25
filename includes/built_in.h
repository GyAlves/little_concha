/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:13:19 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/22 19:31:42 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;

/* Built-in command functions */
void	bi_cd(t_minishell *sh, t_command *cmd);
void	bi_echo(t_minishell *sh, t_command *cmd);
void	bi_env(t_minishell *sh, t_command *cmd);
void	bi_exit(t_minishell *sh, t_command *cmd, \
		char *prompt, t_token *args);
void	bi_export(t_minishell *sh, t_command *cmd);
void	bi_pwd(t_minishell *sh);
void	bi_unset(t_minishell *sh, t_command *cmd);
int		dispatch_builtin(t_minishell *sh, t_command *cmd, \
		char *prompt);
int		bi_from_cd_until_exit(t_minishell *sh, t_command *cmd, \
		char *prompt);
int		bi_from_export_until_unset(t_minishell *sh, t_command *cmd);
int		is_builtin(t_command *cmd);
int		is_parent_builtin(t_command *cmd);

#endif
