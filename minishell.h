#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char	**args; //{"echo", "hello, world", NULL}
	char	*input_file;  // <
	char	*output_file; // >
	char	*delimiter;    // <<
	int		append;       // >>
	int		piped;        // |
}			t_command;

typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
}			t_minishell;

// src/built-in
// src/built-in/bi_cd
void	bi_cd(t_minishell *sh, t_command *cmd);
// src/built-in/bi_echo
void	bi_echo(t_minishell *sh, t_command *cmd);
// src/built-in/bi_env
void	bi_env(t_minishell *sh, t_command *cmd);
// src/built-in/bi_exit
void	bi_exit(t_minishell *sh, t_command *cmd, char *prompt);
// src/built-in/bi_export
void	bi_export(t_minishell *sh, t_command *cmd);
// src/built-in/bi_pwd
void	bi_pwd(t_minishell *sh);
// src/built-in/bi_unset
void	bi_unset(t_minishell *sh, t_command *cmd);
// src/built-in/dispatch_builtin
int		is_builtin(t_command *cmd);
int		dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt);

// src/environment_variables
// src/environment_variables/cpy_n_sort_envar
char	**cpy_and_sort_envar(t_minishell *sh);
void	print_envar(char **envp);
// src/environment_variables/envar_management
char	*find_envar(char **envp, char *key);
void	update_envar(t_minishell *sh, char *key, char *val);
void	free_minishell(t_minishell *sh);
// src/environment_variables/envar_utils
int		is_valid_id(char *envar);
char	*find_envar(char **envp, char *key);
int		cpy_envar_entries(char **new_envp, char **old_envp, int count);
char	*create_envar_entry(char *key, char *val);
// src/environment_variables/first_cpy_env_utils
int		count_init_envar(char **envp);
char	**alloc_init_envar_arr(int count);

// src/utils
// src/utils/cleanup_n_exit
void	cleanup_n_exit(t_minishell *sh, t_command *cmd, char *prompt);
// src/utils/shell_utils
char	**read_input(char **prompt);
int		init_n_exc_cmd(t_minishell *sh, t_command *cmd, \
		char **args, char *prompt);
// src/utils/var_expansion
char	*expand_varriable(t_minishell *sh, char *str);
char	*replace_variables(t_minishell *sh, char *input);

// src/commands
void	exec_cmd(t_minishell *sh, t_command *cmd);
// src/environment_var
char	**get_envar_path(void);
// src/path
char	*set_path(char *cmd);

// Libft/libft
int		ft_isalpha(int c);
int		ft_isalnum(int c);
bool	check_args(char *arg);
size_t	ft_strlen(const char *s);
size_t	ft_arrlen(char **arr);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *str, char separator);
void	free_matrix(char **matrix);

#endif