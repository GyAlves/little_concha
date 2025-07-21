#ifndef SIGNALS_H
# define SIGNALS_H

/* Libs */
# include <signal.h>

/* Headers */
# include "minishell.h"

/* Structs */
typedef struct s_minishell	t_minishell;

// src/signal/signal.c
void	handle_sigint(int sig);
void	setup_shell_signals(void);
void	setup_child_signals(void);

#endif