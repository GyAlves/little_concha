/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:02 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:51:39 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;

/* Generic utility functions */
// src/utils/generic_utils.c
void			free_matrix(token_t *matrix);
// src/utils/main_cleanup_utils.c
void			cleanup_n_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, token_t *args);
void			free_minishell(t_minishell *sh);

#endif