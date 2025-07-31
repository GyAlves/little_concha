/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:46:47 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 20:46:57 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_first_token(t_minishell *shell, t_token *tokens)
{
	if (is_pipe(tokens[0].content))
	{
		print_syntax_err(tokens[0].content);
		shell->exit_status = 2;
		return (false);
	}
	return (true);
}

bool	validate_token_sequence(t_minishell *shell, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].content)
	{
		if (is_str_operator(tokens[i].content) && !tokens[i + 1].content)
		{
			print_syntax_err(NULL);
			shell->exit_status = 2;
			return (false);
		}
		if (is_str_operator(tokens[i].content) \
			&& is_str_operator(tokens[i + 1].content))
		{
			print_syntax_err(tokens[i + 1].content);
			shell->exit_status = 2;
			return (false);
		}
		i++;
	}
	return (true);
}
