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

char	**read_input(t_minishell *shell, char **prompt)
{
	token_t *tokens;

	*prompt = readline(PROMPT);
	if (!*prompt)
	{
		ft_putstr_fd("exit\n", 1);
		shell->exit_status = 0;
		exit (0);
	}
	if (g_sig_status != 0)
	{
		if (g_sig_status == 1)
			shell->exit_status = 130;
		g_sig_status = 0;
	}
	if (**prompt == '\0')
	{
		free(*prompt);
		*prompt = NULL;
		return (NULL);
	}
	add_history(*prompt);
	tokens = lexer(*prompt, shell);
	if (!tokens)
		return (NULL);
	char **result = tokens_parser(tokens, shell);
	free_matrix(tokens);
	return (result);
}
