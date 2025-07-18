/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:02 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;

/* Generic utility functions */
// src/utils/generic_utils.c
void			free_matrix(char **matrix);
// src/utils/main_cleanup_utils.c
void			cleanup_n_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, char **args);
void			free_minishell(t_minishell *sh);

#endif