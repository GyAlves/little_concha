/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:50:35 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/04 15:50:38 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**get_child_tokens_ptr(void)
{
	static t_token	*g_child_tokens = NULL;

	return (&g_child_tokens);
}

void	set_child_tokens(t_token *tokens)
{
	*get_child_tokens_ptr() = tokens;
}

t_token	*get_child_tokens(void)
{
	return (*get_child_tokens_ptr());
}

void	cleanup_child_before_exit(t_minishell *sh, int exit_code)
{
	if (*get_child_tokens_ptr())
		free_tokens(*get_child_tokens_ptr());
	if (sh->envp)
		free_string_matrix(sh->envp);
	if (sh->commands)
		free_commands(sh->commands, sh->total_pipeln_cmd);
	if (sh->original_stdin >= 0)
		close(sh->original_stdin);
	if (sh->original_stdout >= 0)
		close(sh->original_stdout);
	clear_history();
	exit(exit_code);
}
