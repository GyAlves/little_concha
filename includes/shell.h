/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:52:10 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/23 21:15:24 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PROMPT "shell>> "

/* Structs */
typedef struct s_minishell
{
	char		**envp;
	int			exit_status;
	int			total_pipeln_cmd;
	int			original_stdin;
	int			original_stdout;
	int			tokens_count;
	bool		should_exit;
	t_command	*commands;
}			t_minishell;

/* Core shell functions */
//t_minishell *shell_cmd(void);
#endif