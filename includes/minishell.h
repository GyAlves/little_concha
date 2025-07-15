/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:34 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/14 20:25:07 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libs */
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_redir_type
{
	INVALID,
	R_IN,
	R_OUT,
	APPEND,
	HEREDOC
}			t_redir_type;

typedef struct s_std_redir
{
	int	in;
	int	out;
}			t_std_redir;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*filename;
}			t_redirect;

typedef struct s_pipe_data
{
	int		**pipes;
	int		cmd_count;
	pid_t	*pids;
}			t_pipe_data;

/* Headers */
//# include "buil-in.h"
# include "command.h"
//# include "env_var.h"
# include "environment_variables.h"
# include "redirects.h"
# include "shell.h"
# include "tokenization.h"
//# include "utils.h"
# include "libft.h"

// src/built-in
// src/built-in/bi_cd.c
void			bi_cd(t_minishell *sh, t_command *cmd);
// src/built-in/bi_echo.c
void			bi_echo(t_minishell *sh, t_command *cmd);
// src/built-in/bi_env.c
void			bi_env(t_minishell *sh, t_command *cmd);
// src/built-in/bi_exit.c
void			bi_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, char **args);
// src/built-in/bi_export.c
void			bi_export(t_minishell *sh, t_command *cmd);
// src/built-in/bi_pwd.c
void			bi_pwd(t_minishell *sh);
// src/built-in/bi_unset.c
void			bi_unset(t_minishell *sh, t_command *cmd);
// src/built-in/dispatch_builtin.c
int				is_builtin(t_command *cmd);
int				dispatch_builtin(t_minishell *sh, t_command *cmd, \
				char *prompt);

// src/environment_variables
// src/environment_variables/cpy_n_sort_envar.c
char			**cpy_and_sort_envar(t_minishell *sh);
void			print_envar(char **envp);
// src/environment_variables/envar_management.c
char			*find_envar(char **envp, char *key);
void			update_envar(t_minishell *sh, char *key, char *val);
// src/environment_variables/envar_utils.c
int				is_valid_id(char *envar);
char			*find_envar(char **envp, char *key);
int				cpy_envar_entries(char **new_envp, char **old_envp, int count);
char			*create_envar_entry(char *key, char *val);
// src/environment_variables/first_cpy_env_utils.c
int				count_init_envar(char **envp);
char			**alloc_init_envar_arr(int count);


// src/parser_n_lexer/parser.c
// src/parser_n_lexer/parser_utils.c
char			**filter_n_rm_redir(char **args, int *n_count);
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(char **args, t_command *cmd);
// src/parser_n_lexer/token_utils.c
t_redir_type	get_redir_type(char *str);
int				is_redir(char *str);

// src/pipe
// src/pipe/pipe_utils.c
int				setup_pipes(t_pipe_data *data, int cmd_count);
void			close_n_free_parent_pipes(t_pipe_data *data);
void			fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
				t_pipe_data *data, int i);
void			wait_pipe_child(t_pipe_data *data, t_minishell *sh);
// src/pipe/pipe.c
int				handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count);

// src/redirects
// src/redirects/heredoc.c
int				handle_heredoc(t_redirect *redir, t_minishell *sh);
// src/redirects/redirects.c
int				apply_redir(t_redirect *redir);

// src/utils
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

// src/utils/prompt_utils.c
int		exc_cmd(t_minishell *sh, t_command *cmd, char *prompt);

// src/
// src/commands.c
int				apply_heredoc_redir(t_minishell *sh, t_command *cmd);
void			exec_child(t_minishell *sh, t_command *cmd);
int				exec_cmd(t_minishell *sh, t_command *cmd, char *prompt);
// src/environment_var.c
char			**get_envar_path(void);
// src/path.c
char			*set_path(char *cmd);

int				is_parent_builtin(t_command *cmd);

#endif