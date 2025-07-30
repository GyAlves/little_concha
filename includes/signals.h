/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:32:06 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/22 09:32:09 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Libs */
# include <signal.h>

/* Headers */
# include "minishell.h"

/* Forward declarations */
typedef struct s_minishell	t_minishell;

// src/signal/signal.c
void	handle_sigint(int sig);
void	setup_shell_signals(void);
void	setup_child_signals(void);

#endif
