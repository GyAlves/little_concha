#include "../../minishell.h"

char	**read_input(char **prompt)
{
	*prompt = readline("type> ");
	if (!*prompt)
		return (NULL);
	add_history(*prompt);
	return (lexer(*prompt));
}

int	init_n_exc_cmd(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int	status;

	if (!parse_cmd(sh, cmd, args))
		return (1);
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	return (status);
}
