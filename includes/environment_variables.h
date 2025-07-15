/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:29:03 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/13 23:11:28 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_VARIABLES_H
# define ENVIRONMENT_VARIABLES_H

/* Forward declaration */
# include  "minishell.h"
# include  "shell.h"

/* Headers */
//# include "buil-in.h"
# include "command.h"
//# include "env_var.h"
# include "minishell.h"
# include "redirects.h"
# include "shell.h"
# include "tokenization.h"
//# include "utils.h"
# include "libft.h"

/* Functions */
char	**setup_env_variables(int var_count, t_minishell *shell, char **envp);
int	    copy_env_variables(char **new_envp, char **old_envp, int count);

#endif