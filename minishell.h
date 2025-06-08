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

#endif