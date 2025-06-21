#include "minishell.h"

static void	print_cmd_err(char *cmd)
{
	//write(2, "minishell: <", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found!\n", 22);
}

static void	exec_child(t_minishell *sh, t_command *cmd)
{
	char	*path;

	path = set_path(cmd->args[0]);
	if (!path) //if no path is found
	{
		print_cmd_err(cmd->args[0]);
		exit(127);
	}
	cmd->args[0] = path;
	execve(path, cmd->args, sh->envp); //if path is found
	perror("minishell");
	if (path != cmd->args[0])
		free(path);
	exit(127);
}

void	exec_cmd(t_minishell *sh, t_command *cmd)
{
	pid_t	id;
	int		status;

	if (cmd == NULL || cmd->args == NULL)
	{
		perror("invalid cmd!");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork failed!");
		exit(EXIT_FAILURE);
	}
	else if (id == 0)
		exec_child(sh, cmd);
	else if (id > 0)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			sh->exit_status = WEXITSTATUS(status);
	}
}
