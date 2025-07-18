/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:52:10 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/18 19:29:03 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PROMPT "shell>> "

/* Structs */
typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
	int		total_pipeln_cmd;
	int		original_stdin;
	int		original_stdout;
}			t_minishell;

/* Core shell functions */

#endif