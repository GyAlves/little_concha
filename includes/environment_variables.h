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

/* Forward declarations */
typedef struct s_minishell	t_minishell;

/* Environment variable functions */
// src/env_variables/env_variables.c
char	**setup_env_variables(int var_count, t_minishell *shell, char **envp);
int		copy_env_variables(char **new_envp, char **old_envp, int count);
// src/env_variables/envar_management.c
void	update_envar(t_minishell *sh, char *key, char *val);
// src/env_variables/utils/env_validation_utils.c
int		is_valid_id(char *envar);
// src/env_variables/utils/env_search_utils.c
char	*find_envar(char **envp, char *key);
// src/env_variables/utils/env_creation_utils.c
char	*create_envar_entry(char *key, char *val);
int		count_init_envar(char **envp);
char	**alloc_init_envar_arr(int count);
int		cpy_envar_entries(char **new_envp, char **old_envp, int count);
// src/env_variables/utils/env_copy_utils.c
char	**cpy_and_sort_envar(t_minishell *sh);
// src/env_variables/utils/env_sort_utils.c
void	sort_envar(char **envp, int count);
// src/env_variables/utils/env_display_utils.c
void	print_envar(char **envp);
// src/env_variables/utils/env_expansion_utils.c
char	*expand_variable(t_minishell *sh, char *str);
char	*replace_variables(t_minishell *sh, char *input);
// src/path.c
char	*set_path(char *cmd);
char	**get_envar_path(void);

#endif