#ifndef BUILT_IN_H
# define BUILT_IN_H

/* Forward declarations */
typedef struct s_minishell  t_minishell;
typedef struct s_command    t_command;

/* Built-in command functions */
// src/built-in/bi_cd.c
void			bi_cd(t_minishell *sh, t_command *cmd);
// src/built-in/bi_echo.c
void			bi_echo(t_minishell *sh, t_command *cmd);
// src/built-in/bi_env.c
void			bi_env(t_minishell *sh, t_command *cmd);
// src/built-in/bi_exit.c
void			bi_exit(t_minishell *sh, t_command *cmd, \
				char *prompt, char **args);
// src/built-in/bi_export.c
void			bi_export(t_minishell *sh, t_command *cmd);
// src/built-in/bi_pwd.c
void			bi_pwd(t_minishell *sh);
// src/built-in/bi_unset.c
void			bi_unset(t_minishell *sh, t_command *cmd);
// src/built-in/dispatch_builtin.c
int				dispatch_builtin(t_minishell *sh, t_command *cmd, \
				char *prompt);
// src/built-in/utils/built_in_utils.c
int				bi_from_cd_until_exit(t_minishell *sh, t_command *cmd, char *prompt);
int				bi_from_export_until_unset(t_minishell *sh, t_command *cmd);
int				is_builtin(t_command *cmd);
int				is_parent_builtin(t_command *cmd);

#endif