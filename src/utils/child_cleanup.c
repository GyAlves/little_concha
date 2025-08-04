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

static t_token	**child_tokens_ptr(void)
{
	static t_token	*tokens;

	tokens = NULL;
	return (&tokens);
}

void	set_child_tokens(t_token *tokens)
{
	*child_tokens_ptr() = tokens;
}

static t_token	*get_child_tokens(void)
{
	return (*child_tokens_ptr());
}

void	cleanup_child_before_exit(t_minishell *sh, int exit_code)
{
	t_token	*tokens;

	tokens = get_child_tokens();
	if (tokens)
		free_tokens(tokens);
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

void	cleanup_child_with_tokens(t_minishell *sh, t_token *tokens, \
		int exit_code)
{
	if (tokens)
		free_tokens(tokens);
	cleanup_child_before_exit(sh, exit_code);
}
