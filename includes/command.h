/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 19:00:57 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/* FORWARD DECLARATIONS */
typedef struct s_minishell	t_minishell;

/* COMMAND STRUCTURE  */
typedef struct s_command
{
	char	**args;			// Command arguments: {"echo", "hello", NULL}
	char	*input_file;	// Input redirection: < file
	char	*output_file;	// Output redirection: > file
	char	*delimiter;		// Heredoc delimiter: << EOF
	int		append;			// Append mode flag: >> file
	int		piped;			// Pipe flag: cmd1 | cmd2
}			t_command;

/* Functions */
void		exec_cmd(t_minishell *sh, t_command *cmd);
int			cmd_setup(t_minishell *sh, t_command *cmd, char **args, char *prompt);

#endif