/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/08/01 20:37:17 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_n_exit(t_minishell *sh, t_command *cmd, \
char *prompt, t_token *args)
{
	if (cmd)
	{
		free_cmd_struct(cmd);
		free(cmd);
	}
	if (args)
		free_tokens(args);
	if (prompt)
		free(prompt);
	free_minishell(sh);
	exit(sh->exit_status);
}

void	free_minishell(t_minishell *sh)
{
	if (sh->envp)
	{
		free_string_matrix(sh->envp);
	}
	if (sh->commands)
		free_commands(sh->commands, sh->total_pipeln_cmd);
	if (sh->original_stdin >= 0)
		close(sh->original_stdin);
	if (sh->original_stdout >= 0)
		close(sh->original_stdout);
	clear_history();
}

void	free_string_matrix(char **matrix)
{
	int	i;

	if (!matrix)
	{
		return ;
	}
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

void	free_tokens(t_token *token)
{
	int	i;

	if (!token)
		return ;
	i = 0;
	while (token[i].content)
	{
		free(token[i].content);
		token[i].content = NULL;
		i++;
	}
	free(token);
}

void	free_commands(t_command *commands, int cmd_count)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		free_cmd_struct(&commands[i]);
		i++;
	}
	free(commands);
}
