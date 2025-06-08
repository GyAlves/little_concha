#include "../minishell.h"

int	main(int c, char **v, char **envp)
{
	char		*prompt;
	t_command	cmd;

	while (6)
	{
		prompt = readline("type> ");
		if (!prompt) //signal ctrl+d
			break ;
		char	*args[] = {"echo", "hello, world!", NULL};
		cmd.args = args;
		cmd.input_file = NULL;
		cmd.output_file = NULL;
		cmd.piped = 0;
		cmd.append = 0;
		test_cmd(&cmd);
		free (prompt);
	}

	return (0);
}