/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:02 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/15 17:47:52 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Forward declarations */
typedef struct s_minishell  t_minishell;
typedef struct s_command    t_command;
typedef struct s_redirect   t_redirect;
typedef struct s_std_redir  t_std_redir;
typedef struct s_pipe_data  t_pipe_data;

/* Utility functions */
// src/utils/prompt_utils.c
bool	setup_prompt(t_minishell *shell, char **prompt, char ***args);
int		exc_cmd(t_minishell *sh, t_command *cmd, char *prompt);
// src/utils/fd_utils.c
void			save_std_backup(t_std_redir *backup, t_redirect *redir);
void			restore_std_backup(t_std_redir *backup);
// src/utils/free_utils.c
void			cleanup_n_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, char **args);
void			free_matrix(char **matrix);
void			free_minishell(t_minishell *sh);
void			free_cmd_struct(t_command *cmd);
void			close_fd_in_child_pipes(t_pipe_data *pipe_data);
// src/utils/redir_utils.c
int				count_redirs(char **args);
int				fill_redirs(t_command *cmd, char **args);
// src/utils/shell_utils.c
char			**read_input(t_minishell *shell, char **prompt);
int				handle_redir_in_exc(t_minishell \
				*sh, t_command *cmd, t_std_redir *backup);
int				init_n_exc_cmd(t_minishell *sh, t_command **cmd, \
char **args, char *prompt);
// src/utils/var_expansion.c
char			*expand_variable(t_minishell *sh, char *str);
char			*replace_variables(t_minishell *sh, char *input);

#endif