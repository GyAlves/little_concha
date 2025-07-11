/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:21:32 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/07 13:21:33 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_cmd_err(char *cmd_name, char	*error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("/n", 2);
}

int	apply_heredoc_redir(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redirects[i].type == HEREDOC)
		{
			if (!apply_redir(&cmd->redirects[i]))
			{
				sh->exit_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	exec_child(t_minishell *sh, t_command *cmd)
{
	char	*full_cmd_path;

	if (!apply_heredoc_redir(sh, cmd))
		exit(1);
	if (is_builtin(cmd))
	{
		dispatch_builtin(sh,cmd, NULL);
		exit(sh->exit_status);
	}
	if (!cmd->args[0])
	{
		print_cmd_err(NULL, "commmand not found");
		exit(127);
	}
	full_cmd_path = set_path(cmd->args[0]);
	if (!full_cmd_path)
	{
		print_cmd_err(cmd->args[0], "command not found");
		exit(127);
	}
	execve(full_cmd_path, cmd->args, sh->envp);
	perror("minishell");
	if (full_cmd_path != cmd->args[0])
		free(full_cmd_path);
	exit (126);
}

static int	is_parent_builtin(t_command *cmd)
{    
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0 ||
		ft_strcmp(cmd->args[0], "exit") == 0 ||
		ft_strcmp(cmd->args[0], "export") == 0 ||
		ft_strcmp(cmd->args[0], "unset") == 0)
	{
		return (1);
	}
	return (0);
}

void	exec_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
	int			status;
	pid_t		pid;
	t_std_redir	backup; //vai mexer com as bi do processo pai
	t_std_redir	child_backup;

	backup.in = -1;
	backup.out = -1;

	if (cmd->piped || sh->total_pipeln_cmd > 1)
		return (handle_pipes(sh, cmd, sh->total_pipeln_cmd));
	if (is_builtin(cmd) && is_parent_builtin(cmd)) //cd, exit, export, unset no processo pai
	{
		if (!handle_redir_in_exc(sh, cmd, &backup))
		{
			restore_std_backup(&backup);
			return (sh->exit_status);
		}
		dispatch_builtin(sh, cmd, prompt);
		restore_std_backup(&backup);
		return(sh->exit_status);
	}
	else //comando externos ou wcho, env, pwd
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork failed!");
			sh->exit_status = 1;
			exit(1);
		}
		if (pid == 0) //filhote
		{
			child_backup.in = -1;
			child_backup.out = -1;
			if (!handle_redir_in_exc(sh, cmd, &child_backup))
				exit (1);
			exec_child(sh, cmd);
			exit (127);
		}
		else //papai
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				sh->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				sh->exit_status = 128 + WTERMSIG(status);
		}
		return (sh->exit_status);
	}
	
}

