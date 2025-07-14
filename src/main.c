/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:53:21 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/13 22:19:27 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *shell, char **envp) //inicializa a estrutura t_minishell 
{
	setup_env_variables(count_env_variables(envp), shell, envp);

	// sh->envp = alloc_init_envar_arr(count_init_envar(envp));
	// if (!sh->envp)
	// 	return (0);
	// cpy_envar_entries(sh->envp, envp, count_init_envar(envp)); //copia as envar para sh->envp
	// if (!sh->envp[0])
	// {
	// 	free(sh->envp);
	// 	return (0);
	// }
	// sh->exit_status = 0;
	// sh->total_pipeln_cmd = 0;
	// return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_command	cmd;
	char		*prompt;
	char		**args;
	int			status;

	(void)argc;
	(void)argv;
	shell.exit_status = 0;
	if (!setup_env_variables(count_env_variables(envp), shell, envp))
		return (1);
	while (6)
	{
		args = read_input(&prompt);
		if (!args)
			break ;
		status = cmd_setup(&shell, &cmd, args, prompt);
		free_matrix(args);
		free(prompt);
		if (status == -1)
			return (shell.exit_status);
	}
	return (shell.exit_status);
}
