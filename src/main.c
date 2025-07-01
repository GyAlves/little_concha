#include "../minishell.h"

int	main(int c, char **v, char **envp)
{
	t_minishell	sh;
	t_command	cmd;
	char		*prompt;
	char		**args;
	int			status;

	(void)c;
	(void)v;
	sh.envp = alloc_init_envar_arr(count_init_envar(envp));
	if (!cpy_envar_entries(sh.envp, envp, count_init_envar(envp)))
		return (1);
	sh.exit_status = 0;
	while (6)
	{
		args = read_input(&prompt);
		if (!args)
		{
			free_minishell(&sh);
			break ;
		}
		status = init_n_exc_cmd(&sh, &cmd, args, prompt);
		free_matrix(args);
		free (prompt);
		if (status == -1)
		{
			free_minishell(&sh);
			return (sh.exit_status);
		}
	}
	free_minishell(&sh);
	return (sh.exit_status);
}
