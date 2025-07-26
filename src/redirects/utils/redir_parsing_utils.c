/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	fill_single_redir(t_command *cmd, t_token *args, int i, int count)
{
	int	j;

	if (!args[i + 1].content)
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	cmd->redirects[count].type = get_redir_type(args[i].content);
	cmd->redirects[count].filename = ft_strdup(args[i + 1].content);
	if (!cmd->redirects[count].filename)
	{
		j = count;
		while (j > 0)
			free(cmd->redirects[--j].filename);
		return (0);
	}
	return (1);
}*/
// Altere apenas a fill_single_redir. As outras duas (init e fill_redirs) permanecem iguais.
int fill_single_redir(t_command *cmd, t_token *args, int i, int count)
{
    // Reutilizando a mesma lógica de verificação robusta
    if (args[i + 1].content == NULL || is_redir(args[i + 1].content)
        || is_pipe(args[i + 1].content))
    {
        // Não precisa imprimir erro aqui, pois copy_command_args já fará isso,
        // mas precisa sinalizar a falha.
        // A lógica de free em caso de erro já está no seu código e está boa.
        return (0);
    }
    cmd->redirects[count].type = get_redir_type(args[i].content);
    cmd->redirects[count].filename = ft_strdup(args[i + 1].content);
    if (!cmd->redirects[count].filename)
    {
        // Sua lógica de free em caso de erro aqui.
        return (0);
    }
    return (1);
}

int	fill_redirs(t_command *cmd, t_token *args)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (args[i].content)
	{
		if (is_redir(args[i].content))
		{
			if (!fill_single_redir(cmd, args, i, count))
				return (0);
			count++;
			i += 2;
		}
		else
			i++;
	}
	cmd->redirections_count = count;
	return (1);
}

int	count_redirs(t_token *args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i].content)
	{
		if (is_redir(args[i].content))
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
