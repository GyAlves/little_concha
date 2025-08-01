/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:16:18 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/08/01 20:31:50 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_input(t_minishell *shell, char **prompt_line, t_token **tokens)
{
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
