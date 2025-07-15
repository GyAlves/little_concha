/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:42:23 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/15 19:50:13 by galves-a         ###   ########.fr       */
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