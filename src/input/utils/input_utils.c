/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:14:59 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_signals(t_minishell *shell)
{
	if (g_sig_status != 0)
	{
		if (g_sig_status == 1)
			shell->exit_status = 130;
		g_sig_status = 0;
	}
}

static bool	read_and_validate_prompt(char **prompt, t_minishell *shell)
{
	*prompt = readline(PROMPT);
	if (!*prompt)
	{
		ft_putstr_fd("exit\n", 1);
		// Idealmente, chame aqui uma função que libera todos os recursos
		exit(0);
	}
	if (**prompt == '\0')
	{
		free(*prompt);
		*prompt = NULL;
		return (false);
	}
	return (true);
}

char	**read_input(t_minishell *shell, char **prompt)
{
	t_token	*tokens;
	char	**result;

	handle_input_signals(shell);
	if (!read_and_validate_prompt(prompt, shell))
		return (NULL);
	add_history(*prompt);
	tokens = lexer(*prompt, shell);
	if (!tokens)
		return (NULL);
	result = tokens_parser(tokens, shell);
	free_tokens(tokens); // Observação sobre esta linha abaixo
	return (result);
}

