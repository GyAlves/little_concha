/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:37:52 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/06 17:37:55 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_minishell(t_minishell *sh, char **envp) //inicializa a estrutura t_minishell 
{
	sh->envp = alloc_init_envar_arr(count_init_envar(envp)); //aloca memoria em sh->envp
	if (!sh->envp)
		return (0);
	cpy_envar_entries(sh->envp, envp, count_init_envar(envp)); //copia as envar para sh->envp
	if (!sh->envp[0])
	{
		free(sh->envp);
		return (0);
	}
	sh->exit_status = 0;
	sh->total_pipeln_cmd = 0;
	return (1);
}

int	main(int c, char **v, char **envp)
{
	int			i;
	t_minishell	sh;
	t_command	*cmd;
	char		*prompt;
	char		**args;

	(void)c;
	(void)v;
	if (!init_minishell(&sh, envp)) //se ocorrer um erro durante a inicialização da estrutura t_minishell, retorne erro
		return (1);
	while (6)
	{
		args = read_input(&sh, &prompt); //args salva o prompt(o mano que recebe o input do user) ja tokenizado
		if (!args) //se não existem tokens para processar
		{
			if (prompt) //verifica se prompt não é null antes de tentar liberar
			{
				free(prompt); //liberar memoria alocada pelo radliine
				prompt = NULL; //definir como null para receber outro input
			}
			if (sh.exit_status == 111) //terminar o programa com ctrl+d (não funciona ainda)
				break ;
			continue ; //volta para o inicio do loop
		}
		cmd = NULL;
		sh.exit_status = init_n_exc_cmd(&sh, &cmd, args, prompt);
		if (cmd)
		{
			i = 0;
			while ( i < sh.total_pipeln_cmd)
			{
				free_cmd_struct(&cmd[i]);
				i++;
			}
			free(cmd);
			cmd = NULL;
		}
		free_matrix(args);
		args = NULL;
		free(prompt);
		prompt = NULL;
		if (sh.exit_status == 111)
			break ;
	}
	free_minishell(&sh);
	return (sh.exit_status);
}
