#include "../../minishell.h"

static int	init_cmd_redir(t_command *cmd, char **args) //inicializa a struct de redir 
{
	cmd->redir_count = count_redirs(args); //adiciona a contagem de redirs a struct
	cmd->redirects = ft_calloc(cmd->redir_count + 1, sizeof(t_redirect)); //aloca memoria para a struct de redir
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args)) //confere os argumentos passados 
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}