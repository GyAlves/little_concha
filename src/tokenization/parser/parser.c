/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/25 17:39:17 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_tokens(t_minishell *shell, t_token *tokens)
{
	int		i;
	char	*content_original;

	i = 0;
	if (!tokens)
		return (true);
	while (tokens[i].content)
	{
		content_original = tokens[i].content;
		if (tokens[i].was_single)
			tokens[i].content = single_quoted_token(content_original);
		else if (tokens[i].was_double)
			tokens[i].content = double_quoted_token(content_original, shell);
		else
			tokens[i].content = non_quoted_token(content_original, shell);
		free(content_original);
		if (!tokens[i].content)
		{
			perror("minishell: expansion malloc failed");
			shell->exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}
