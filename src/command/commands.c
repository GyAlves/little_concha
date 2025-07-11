/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:45:16 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/11 20:42:56 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void exec_child(t_minishell *sh, t_command *cmd);

int	cmd_setup(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int	status;

	cmd->args = args;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->piped = 0;
	cmd->append = 0;
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	return (status);
}

void	exec_cmd(t_minishell *sh, t_command *cmd)
{
	pid_t	id;
	int		status;

	if (cmd == NULL || cmd->args == NULL)
	{
		perror("invalid cmd!");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork failed!");
		exit(EXIT_FAILURE);
	}
	else if (id == 0)
		exec_child(sh, cmd);
	else if (id > 0)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			sh->exit_status = WEXITSTATUS(status);
	}
}

static void	exec_child(t_minishell *sh, t_command *cmd)
{
	char	*path;

	path = set_path(cmd->args[0]);
	if (!path)
	{
		print_cmd_err(cmd->args[0]);
		exit(127);
	}
	cmd->args[0] = path;
	execve(path, cmd->args, sh->envp);
	if (path != cmd->args[0])
		free(path);
	exit(127);
}