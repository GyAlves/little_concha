/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/14 13:58:01 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_minishell(t_minishell *shell, char **envp)
{
	setup_env_variables(count_init_envar(envp), shell, envp);
	if (!shell->envp[0])
	{
		free(shell->envp);
		return (0);
	}
	shell->exit_status = 0;
	shell->total_pipeln_cmd = 0;
	return (1);
}

static bool	setup_prompt(t_minishell *shell, char **prompt, char ***args)
{	
	*args = read_input(shell, prompt);
	if (!*args)
	{
		if (*prompt)
		{
			free(*prompt);
			*prompt = NULL;
		}
		return (false);
	}
	return (true);
}

static void	setup_command(t_command **cmd, t_minishell *shell, char **prompt, char ***args)
{
	int	counter;

	*cmd = NULL;
	shell->exit_status = init_n_exc_cmd(shell, cmd, *args, *prompt);
	if (*cmd)
	{
		counter = 0;
		while (counter < shell->total_pipeln_cmd)
		{
			free_cmd_struct(&(*cmd)[counter]);
			counter++;
		}
		free(*cmd);
		*cmd = NULL;
	}
}

int	main(int c, char **v, char **envp)
{
	t_minishell	shell;
	t_command	*cmd;
	char		*prompt;
	char		**args;

	(void)c;
	(void)v;
	if (!init_minishell(&shell, envp))
		return (1);
	while (6)
	{
		if (!setup_prompt(&shell, &prompt, &args))
		{
			if (shell.exit_status == 111)
				break ;
			continue;
		}
		setup_command(&cmd, &shell, &prompt, &args);
		free_matrix(args);
		args = NULL;
		free(prompt);
		prompt = NULL;
		if (shell.exit_status == 111)
			break ;
	}
	free_minishell(&shell);
	return (shell.exit_status);
}
