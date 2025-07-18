/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:43:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/18 19:27:19 by galves-a         ###   ########.fr       */
=======
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:43:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/13 22:44:03 by gyasminalve      ###   ########.fr       */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**setup_env_variables(int var_count, t_minishell *shell, char **envp)
{
	char	**new_envp;

	new_envp = ft_calloc(var_count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	shell->envp = new_envp;
	if (!copy_env_variables(shell->envp, envp, var_count))
		return (NULL);
	return (new_envp);
}
