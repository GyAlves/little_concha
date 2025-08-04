/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/01 20:43:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_status = 0;

int	main(int c, char **v, char **envp)
{
	int	status;

	(void)c;
	(void)v;
	if (!init_minishell(shell_cmd(), envp))
		return (1);
	(shell_cmd())->original_stdin = dup(STDIN_FILENO);
	(shell_cmd())->original_stdout = dup(STDOUT_FILENO);
	setup_shell_signals();
	status = run_shell_loop(shell_cmd());
	clear_history();
	free_minishell(shell_cmd());
	return (status);
}
