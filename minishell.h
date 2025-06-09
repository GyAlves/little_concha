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
	int		delimiter;    // <<
	int		append;       // >>
	int		piped;        // |
}			t_command;

//src
////commands
void	test_cmd(t_command *cmd);
void	exec_cmd(t_command *cmd);
////environment_var
int		envar_handler(int c, char **v, char **envp);
//Libft
////libft
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *str, char separator);

#endif