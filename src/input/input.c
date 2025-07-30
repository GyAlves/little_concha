/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:16:18 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/22 19:41:09 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_input(t_minishell *shell, char **prompt_line, t_token **tokens)
{
	handle_input_signals(shell);

	if (!read_and_validate_prompt(prompt_line, shell))
		return (false);
	add_history(*prompt_line);
	*tokens = lexer(*prompt_line, shell);
	if (!*tokens)
	{
		free(*prompt_line);
		*prompt_line = NULL;
		return (false);
	}
	return (true);
}
