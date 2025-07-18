/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:54:41 by gyasminalve       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/18 19:28:54 by galves-a         ###   ########.fr       */
=======
/*   Updated: 2025/07/16 09:19:01 by gyasminalve      ###   ########.fr       */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

<<<<<<< HEAD
/* Forward declarations */
typedef struct s_redirect	t_redirect;
typedef struct s_pipe_data	t_pipe_data;
typedef struct s_minishell	t_minishell;
=======
typedef struct s_redirect   t_redirect;
typedef struct s_pipe_data  t_pipe_data;
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

/* COMMAND STRUCTURE */
typedef struct s_command
{
<<<<<<< HEAD
	char		**args;
	int			redirections_count;
	bool		is_piped;
	t_redirect	*redirects;
	t_pipe_data	*pipe;
}			t_command;
=======
	char			**args;
	int				redirections_count;
	int				is_piped;
	t_redirect		*redirects;
	t_pipe_data		*pipe;
}	t_command;
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

typedef struct s_cmd_init
{
	int		cmd_count;
	char	**cmd_args;
<<<<<<< HEAD
}			t_cmd_init;

/* Command functions */
// src/command/command.c
int		init_command(t_minishell *sh, t_command **cmd, \
		char **args, char *prompt);
int		init_command_arr(t_command **cmd, int cmd_count);
int		handle_single_cmd(t_command **cmd, char **args);
int		handle_multi_cmd(t_command **cmd, char **args);
int		count_command_args(char **args);
char	**copy_command_args(char **args, char **n_args);
void	cleanup_command(t_command *cmd);
bool	parse_single_cmd(t_command *cmd, char **args, int start);
int		init_cmd_redirection(t_command *cmd, char **args);
void	setup_command(t_command **cmd, t_minishell *shell, \
		char **prompt, char ***args);
// src/commands.c
// src/command/utils/command_execution_utils.c
int		exec_command(t_minishell *sh, t_command *cmd, char *prompt);
int		exec_external_cmd(t_minishell *sh, t_command *cmd, char *prompt);
// src/command/utils/command_child_process_utils.c
void	exec_cmd_in_child(t_minishell *sh, t_command *cmd);
// src/command/utils/command_cleanup_utils.c
void	free_cmd_struct(t_command *cmd);
void	print_cmd_err(char *cmd_name, char	*error_msg);
=======
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
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

#endif