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

// src/builtin/utils/built_int_utils.c
int		is_builtin(t_command *cmd);
int		is_parent_builtin(t_command *cmd);
void	print_cd_no_file_nor_dir(char *path);
// src/builtin/*.c
void	bi_cd(t_minishell *sh, t_command *cmd);
void	bi_echo(t_minishell *sh, t_command *cmd);
void	bi_env(t_minishell *sh, t_command *cmd);
void	bi_exit(t_minishell *shell, t_command *cmd);
void	bi_export(t_minishell *sh, t_command *cmd);
void	bi_pwd(t_minishell *sh);
void	bi_unset(t_minishell *sh, t_command *cmd);
// src/builtin/dispatch_builtin.c
void	dispatch_builtin(t_minishell *sh, t_command *cmd);

#endif
