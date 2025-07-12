/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:41:58 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/12 17:30:39 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

#include "minishell.h"

/* Functions */
char	**setup_env_variables(int var_count, t_minishell shell, char **envp);
int	    count_env_variables(char **envp);
int	    copy_env_variables(char **new_envp, char **old_envp, int count);
#endif