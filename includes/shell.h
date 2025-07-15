/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:52:10 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/14 14:03:26 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PROMPT "shell>> "

/* Structs */
typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
	int		total_pipeln_cmd;
} t_minishell;

/* Headers */
//# include "buil-in.h"
# include "command.h"
//# include "env_var.h"
# include "environment_variables.h"
# include "minishell.h"
# include "redirects.h"
# include "tokenization.h"
//# include "utils.h"
# include "libft.h"

#endif