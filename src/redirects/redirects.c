/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redir(t_redirect *redir)
{
	if (redir->type == R_IN)
		return (input_redir(redir));
	else if (redir->type == R_OUT)
		return (output_redir(redir));
	else if (redir->type == APPEND)
		return (append_redir(redir));
	else if (redir->type == HEREDOC)
		return (heredoc_redir(redir));
	return (0);
}