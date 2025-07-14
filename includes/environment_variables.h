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
struct s_minishell;

/* Functions */
char	**setup_env_variables(int var_count, struct s_minishell *shell, char **envp);
int	    copy_env_variables(char **new_envp, char **old_envp, int count);

#endif