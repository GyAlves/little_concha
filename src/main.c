/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/08/01 20:43:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_status = 0;

t_minishell	*shell_cmd(void)
{
	static t_minishell	shell_instance;

	return (&shell_instance);
}

static int	init_minishell(t_minishell *shell, char **envp)
{
	int env_count;
	
	env_count = count_init_envar(envp);
	shell->envp = NULL; 
	setup_env_variables(env_count, shell, envp);
	if (!shell->envp[0])
	{
		free(shell->envp);
		return (0);
	}
	shell->exit_status = 0;
	shell->total_pipeln_cmd = 0;
	shell->commands = NULL;
	shell->should_exit = false;
	return (1);
}

static int	run_shell_loop(t_minishell *shell)
{
	char	*prompt_line;
	t_token	*tokens;

	while (shell->should_exit == false)
	{
		prompt_line = NULL;
		tokens = NULL;
		if (!read_input(shell, &prompt_line, &tokens))
			continue ;
		if (expand_tokens(shell, tokens))
		{
			set_child_tokens(tokens);
			if (parse_input(shell, tokens))
				execute_pipeline(shell);
			set_child_tokens(NULL);
		}
		free_tokens(tokens);
		free(prompt_line);
		if (shell->commands)
		{
			cleanup_heredoc_files(shell->commands);
			free_commands(shell->commands, shell->total_pipeln_cmd);
		}
		shell->commands = NULL;
	}
	return (shell->exit_status);
}

int	main(int c, char **v, char **envp)
{
	int	status;

	(void)c;
	(void)v;
	if (!init_minishell(shell_cmd(), envp))
		return (1);
	(shell_cmd())->original_stdin = dup(STDIN_FILENO);
	(shell_cmd())->original_stdout = dup(STDOUT_FILENO);
	setup_shell_signals();
	status = run_shell_loop(shell_cmd());
	clear_history();
	free_minishell(shell_cmd());
	return (status);
}
