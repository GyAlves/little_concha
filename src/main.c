#include "../minishell.h"

int	main(int c, char **v, char **envp)
{
	t_minishell	ms;
	t_command	cmd;
	char		*prompt;
	char		**args;
	int			status;

	(void)c;
	(void)v;
	ms.envp = envp;
	ms.exit_status = 0;
	while (6)
	{
		args = read_input(&prompt);
		if (!args)
			break ;
		status = init_n_exc_cmd(&ms, &cmd, args, prompt);
		free_matrix(args);
		free (prompt);
		if (status == -1)
			return (ms.exit_status);
	}
	return (ms.exit_status);
}
