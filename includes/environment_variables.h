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
typedef struct s_minishell  t_minishell;

/* Environment variable functions */
char	**setup_env_variables(int var_count, t_minishell *shell, char **envp);
int	    copy_env_variables(char **new_envp, char **old_envp, int count);
void			update_envar(t_minishell *sh, char *key, char *val);
int				is_valid_id(char *envar);
char			*find_envar(char **envp, char *key);
char			*create_envar_entry(char *key, char *val);
int				count_init_envar(char **envp);
char			**alloc_init_envar_arr(int count);
int				cpy_envar_entries(char **new_envp, char **old_envp, int count);
char			**cpy_and_sort_envar(t_minishell *sh);
void			sort_envar(char **envp, int count);
void			print_envar(char **envp);
char			*expand_variable(t_minishell *sh, char *str);
char			*replace_variables(t_minishell *sh, char *input);
char			*set_path(char *cmd);
char			**get_envar_path(void);

#endif