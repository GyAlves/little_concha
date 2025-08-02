/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:54:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/22 20:00:34 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

/* Forward declarations */
typedef struct s_redirect	t_redirect;
typedef struct s_pipe_data	t_pipe_data;
typedef struct s_token		t_token;
typedef struct s_minishell	t_minishell;
typedef struct s_std_redir	t_std_redir;

/* STRUCTS */
typedef struct s_command
{
	char		**args;
	int			redirections_count;
	bool		is_piped;
	t_redirect	*redirects;
	t_pipe_data	*pipe;
}			t_command;

typedef struct s_cmd_init
{
	int		cmd_count;
	char	**cmd_args;
}			t_cmd_init;

// src/utils/commanda_token_validation.c
bool	validate_first_token(t_minishell *shell, t_token *tokens);
bool	validate_token_sequence(t_minishell *shell, t_token *tokens);
// src/utils/command_args_utils.c
int		count_command_args(t_token *args);
bool	validate_tokens(t_minishell *shell, t_token *tokens);
char	**copy_command_args(t_token *args, char **n_args);
// src/utils/command_child_process_utils.c
void	exec_cmd_in_child(t_minishell *sh, t_command *cmd);
// src/utils/command_execution_utils.c
int		handle_parent_bi_exec(t_minishell *sh, t_command *cmd);
int		exec_external_cmd(t_minishell *sh, t_command *cmd, char *prompt);
// src/utils/command_logging_utils.c
void	print_cmd_err(char *cmd_name, char	*error_msg);
void	print_syntax_err(const char *token);
// src/utils/command_memory_utils.c
int		init_command_arr(t_command **cmd, int cmd_count);
void	cleanup_command(t_command *cmd);
void	free_cmd_struct(t_command *cmd);
void	cleanup_heredoc_files(t_command *cmd);
// src/utils/command_parse_utils.c
bool	init_cmd_redirection(t_command *cmd, t_token *args);
bool	parse_single_cmd(t_command *cmd, t_token *args, int start);
int		handle_single_cmd(t_command **cmd, t_token *args);
int		handle_multi_cmd(t_command **cmd, t_token *args);
// src/command/command.c
void	execute_pipeline(t_minishell *shell);
bool	parse_input(t_minishell *shell, t_token *tokens);

#endif