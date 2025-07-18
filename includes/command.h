/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:54:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/18 19:50:13 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

typedef struct s_redirect   t_redirect;
typedef struct s_pipe_data  t_pipe_data;
typedef struct s_std_redir  t_std_redir;

typedef struct s_pipe_io_fd
{
	int		*in;
	int		*out;
}	t_pipe_io_fd;

/* COMMAND STRUCTURE */
typedef struct s_command
{
	char			**args;
	int				redirections_count;
	int				is_piped;
	t_redirect		*redirects;
	t_pipe_data		*pipe;
}	t_command;

typedef struct s_cmd_init
{
	int		cmd_count;
	char	**cmd_args;
}	t_cmd_init;

/* Forward declarations */
typedef struct s_minishell  t_minishell;

/* Command functions */
int				init_command(t_minishell *sh, t_command **cmd, char **args, \
					char *prompt);
int				init_command_arr(t_command **cmd, int cmd_count);
int				handle_single_cmd(t_command **cmd, char **args);
int				handle_multi_cmd(t_command **cmd, char **args);
int				count_command_args(char **args);
char			**copy_command_args(char **args, char **n_args);
void			cleanup_command(t_command *cmd);
bool			parse_single_cmd(t_command *cmd, char **args, int start);
int				init_cmd_redirection(t_command *cmd, char **args);
void			setup_command(t_command **cmd, t_minishell *shell, \
					char **prompt, char ***args);
void			exec_child(t_minishell *sh, t_command *cmd);
int				exec_cmd(t_minishell *sh, t_command *cmd, char *prompt);
int				exc_cmd(t_minishell *sh, t_command *cmd, char *prompt);
void			free_cmd_struct(t_command *cmd);
void			print_cmd_err(char *cmd_name, char *error_msg);
void			fork_n_redirect_pipe(t_minishell *sh, t_command *cmd, \
					t_pipe_data *data, int i);
void			close_fd_in_child_pipes(t_pipe_data *pipe_info);
int				handle_redir_in_exc(t_minishell *sh, t_command *cmd, \
					t_std_redir *backup);

#endif