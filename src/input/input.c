/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:16:18 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/16 09:16:30 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	setup_prompt(t_minishell *shell, char **prompt, char ***args)
{	
	*args = read_input(shell, prompt);
	if (!*args)
	{
		if (*prompt)
		{
			free(*prompt);
			*prompt = NULL;
		}
		return (false);
	}
	return (true);
}