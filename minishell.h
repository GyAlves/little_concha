#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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


// src/built_in
int 	is_builtin(t_command *cmd);
void	builtin_env(t_minishell *ms, t_command *cmd);
// src/commands
void	print_cmd_err(char *cmd);
void	exec_cmd(t_minishell *ms, t_command *cmd);
// src/environment_var
char	**get_envar_path(void);
// src/path
char	*set_path(char *cmd);
// Libft/libft
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *str, char separator);
void	free_matrix(char **matrix);

#endif