#include "../minishell.h"

int	main(int c, char **v, char **envp)
{
	t_minishell	ms;
	t_command	cmd;
	char		*prompt;
	char		**args;
	c = 0;
	v = NULL;
	ms.envp = envp;
	ms.exit_status = 0;
	while (6)
	{
		prompt = readline("type> ");
		if (!prompt) //signal ctrl+d
			break ;
		add_history(prompt);
		args = ft_split(prompt, ' ');
		if (!args)
			continue ;
		cmd.args = args;
		cmd.input_file = NULL;
		cmd.output_file = NULL;
		cmd.piped = 0;
		cmd.append = 0;
		exec_cmd(&ms, &cmd);
		free_matrix(args);
		free (prompt);
	}
	return (0);
}