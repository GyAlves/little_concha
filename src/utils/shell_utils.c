#include "../../minishell.h"

char	**read_input(char **prompt)
{
	char	**args;

	*prompt = readline("type> ");
	if (!*prompt)
		return (NULL);
	add_history(*prompt);
	args = ft_split(*prompt, ' ');
	return (args);
}

int	init_n_exc_cmd(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int	status;

	cmd->args = args;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->piped = 0;
	cmd->append = 0;
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	return (status);
}
