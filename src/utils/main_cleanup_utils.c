/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:51:26 by gyasminalve      ###   ########.fr       */
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
		free_matrix(args);
	if (prompt)
		free(prompt);
	free_minishell(sh);
	exit(sh->exit_status);
}

void	free_minishell(t_minishell *sh)
{
	if (sh->envp)
		free_string_matrix(sh->envp);
	clear_history();
}

void	free_string_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

void	free_matrix(t_token *matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i].content)
	{
		free(matrix[i].content);
		matrix[i].content = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
