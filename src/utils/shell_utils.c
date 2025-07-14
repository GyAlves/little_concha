#include "../../minishell.h"

char	**read_input(t_minishell *sh, char **prompt) //chama readline() que captura o input do user, add o historico, por ultimo, passamos para o lexer para inicializar a tokenização
{
	*prompt = readline("type> ");
	if (!*prompt)
    {
        sh->exit_status = 111; // Sinalizar Ctrl+D
        return (NULL);
    }
	if (!*prompt || **prompt == '\0')
		return (NULL);
	add_history(*prompt);
	return (lexer(*prompt));
}

static int	process_single_redir(t_redirect *redir, t_std_redir *backup)
{
	save_std_backup(backup, redir);
	if (!apply_redir(redir))
		return (0);
	return (1);
}

static int	process_all_heredocs(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redirects[i].type == HEREDOC)
		{
			if (!handle_heredoc(&cmd->redirects[i], sh))
			{
				sh->exit_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	handle_redir_in_exc(t_minishell \
	*sh, t_command *cmd, t_std_redir *backup)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (!process_single_redir(&cmd->redirects[i], backup))
		{
			sh->exit_status = 1;
			restore_std_backup(backup);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	exec_cmd(t_minishell *sh, t_command *cmd, char *prompt) //executa pipe, redir, bi ou comandos externos
{
	int			status;
	t_std_redir	backup;

	backup.in = -1; //armazena a copia dos fd antes dos redir, inicializa com -1 para indicar que não existe fd salvo
	backup.out = -1; //armazena a copia dos fd antes dos redir, inicializa com -1 para indicar que não existe fd salvo
	if (!process_all_heredocs(sh, cmd)) //processa heredocs
		return (1);
	if (cmd->piped)
		return (handle_pipes(sh, cmd, count_cmd_args(cmd->args))); //se pipe existir tratamos pipes
	if (is_builtin(cmd) && is_parent_builtin(cmd))
	{
		if (!handle_redir_in_exc(sh, cmd, &backup))
		{
			restore_std_backup(&backup);
			return (sh->exit_status);
		}
		dispatch_builtin(sh, cmd, prompt);
		restore_std_backup(&backup);
		return (sh->exit_status);
	}
	else
	{
		exec_child(sh, cmd, prompt);
		status = sh->exit_status;
	}
	return (status);
}

int	init_n_exec_cmd(t_minishell *sh, t_command **cmd, char **args, char *prompt) //faz o parsing e a execução do comando
{
	int	status;

	if (!parse_n_init_cmd(sh, cmd, args)) //parsing
		return (1);
	status = exec_cmd(sh, *cmd, prompt); //executa o cmd armazenado e armazena o resultado em status
	return (status); //retorna o starus da execução, se deu bom ou nn
}
