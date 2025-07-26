/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:50:13 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	fill_cmd(t_token *args, t_command *cmd)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (args[i].content)
	{
		if (is_pipe(args[i].content) || args[i + 1].content == NULL)
		{
			if (!parse_single_cmd(&cmd[j], args, start))
			{
				while (j-- > 0)
					free_cmd_struct(&cmd[j]);
				return (0);
			}
			start = i + 1;
			j++;
		}
		i++;
	}
	return (1);
}*/

int fill_cmd(t_minishell *sh, t_command *cmd, t_token *args)
{
    int i;
    int j;
    int start;
    int status;

    i = 0;
    j = 0;
    start = 0;
    while (args[i].content)
    {
        if (is_pipe(args[i].content) || args[i + 1].content == NULL)
        {
            // Chamamos a nova parse_single_cmd, passando 'sh'
            status = parse_single_cmd(sh, &cmd[j], args, start);
            if (status != 0) // Verificamos se houve erro
            {
                // Se houve, fazemos a limpeza dos comandos já parseados
                while (j-- > 0)
                    free_cmd_struct(&cmd[j]);
                return (status); // E propagamos o código de erro
            }
            start = i + 1;
            j++;
        }
        i++;
    }
    return (0); // Sucesso
}

int	init_cmd_arr(t_command **cmd, int cmd_count)
{
	*cmd = ft_calloc(cmd_count, sizeof(t_command));
	if (!*cmd)
		return (0);
	return (1);
}
