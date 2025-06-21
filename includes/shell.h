/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 18:39:25 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/* STRUCTS DECLARATIONS  */
typedef struct s_command	t_command;

/* SHELL STRUCT  */
typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
}			t_minishell;

/* SHELL INITIALIZATION  */
void	init_shell(t_minishell *shell, char **envp);
void	cleanup_shell(t_minishell *shell);

/* SHELL UTILITIES  */
void	cleanup_n_exit(t_minishell *sh, t_command *cmd, char *prompt);

/* ENVIRONMENT VARIABLES  */
char	*find_envar(char **envp, char *key);
void	update_envar(t_minishell *sh, char *key, char *val);
char	**get_envar_path(void);

/* PATH RESOLUTION */
char	*set_path(char *cmd);

#endif