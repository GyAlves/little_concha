/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_management_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:31:41 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 13:57:55 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parse_n_init_cmd(t_minishell *sh, t_command **cmd, char **args) 
{
	int	cmd_count;

	if (!args || !args[0])
		return (0);
	cmd_count = count_pipes(args); //cmd_count armazena a qnt de pipes que apareceram
	sh->total_pipeln_cmd = cmd_count; //aqui armazenamos a qnt em uma struct
	if (!init_cmd_arr(cmd, cmd_count)) //se falhar em alocar memoria para cmd
		return (0);
	if (cmd_count == 1) //se a qnt de pipe for 1
	{
		if (!parse_single_cmd(*cmd, args, 0)) //confere se existem pipes e redirs
		{
			free(*cmd);
			return (0);
		}
		(*cmd)->piped = 0;
	}
	else
	{
		(*cmd)->piped = 1;
		if (!fill_cmd(args,*cmd))
		{
			free_cmd_struct(*cmd);
			free(*cmd);
			return (0);
		}
	}
	return (1);
}
