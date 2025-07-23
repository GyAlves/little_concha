/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:56:05 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

token_t	*read_input(t_minishell *shell, char **prompt)
{
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
	return (lexer(*prompt));
}
