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

static bool	validate_space(const char *prompt)
{
	if (!prompt)
		return (false);
	while (*prompt)
	{
		if (!ft_isspace(*prompt))
			return (true);
		prompt++;
	}
	return (false);
}

bool	read_and_validate_prompt(char **prompt, t_minishell *shell)
{
	*prompt = readline(PROMPT);
	if (!*prompt)
	{
		if (g_sig_status != 1)
		{
			ft_putstr_fd("exit\n", 1);
			shell->should_exit = true;
		}
		return (false);
	}
	if (**prompt == '\0')
	{
		free(*prompt);
		*prompt = NULL;
		return (false);
	}
	if (!validate_space(*prompt))
	{
		free(*prompt);
		*prompt = NULL;
		return (false);
	}
	return (true);
}
