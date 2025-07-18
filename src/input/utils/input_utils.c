/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/18 19:41:38 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input(t_minishell *shell, char **prompt)
{
	//função de conferir sinal aqui 
	*prompt = readline(PROMPT);
	if (!*prompt)
	{
		shell->exit_status = 111; //sig
		exit (0);
	}
	if (!*prompt || **prompt == '\0')
		return (NULL);
	add_history(*prompt);
	return (lexer(*prompt));
}