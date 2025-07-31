/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	get_redir_type(char *str)
{
	if (!str)
		return (INVALID);
	if (!ft_strcmp(str, ">"))
		return (R_OUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<"))
		return (R_IN);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (INVALID);
}

int	is_pipe(char *str)
{
	return (str && ft_strcmp(str, "|") == 0);
}

int	is_operator(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

int	is_str_operator(char *str)
{
	if (!str)
		return (0);
	if (get_redir_type(str) != INVALID || is_pipe(str))
		return (1);
	return (0);
}
