/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:02 by galves-a          #+#    #+#             */
/*   Updated: 2025/08/01 19:49:12 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;

/* Generic utility functions */
// src/utils/generic_utils.c
void			free_tokens(t_token *matrix);
void			free_string_matrix(char **matrix);
// src/utils/main_cleanup_utils.c
void			cleanup_n_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, t_token *args);
void			free_minishell(t_minishell *sh);
void			free_commands(t_command *commands, int cmd_count);
void 			cleanup_child_before_exit(t_minishell *sh, int exit_code);
void			cleanup_child_with_tokens(t_minishell *sh, t_token *tokens, int exit_code);
void			set_child_tokens(t_token *tokens);

#endif