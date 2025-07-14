#include "../../minishell.h"

static int	count_pipes(char **args) //conta a quantidade de pipes que tem na linha de comando e itera count para retornar posteriormente
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (args[i])
	{
		if (is_pipe(args[i]))
			count++;
		i++;
	}
	return (count);
}

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

int	parse_single_cmd(t_command *cmd, char **args, int start) //inicializa a struct para um unico comando, conta argumentos e redirs
{
	int		n_count;
	char	**cmd_args;

	if (!cmd || !args)
		return (0);
	cmd->piped = 0; //inicializa na struct
	cmd->redir_count = 0; //inicializa na struct
	n_count = count_cmd_args(args + start);
	cmd_args = ft_calloc(n_count + 1, sizeof(char *)); //aloca memoria para esse arr de arr 
	if (!cmd_args)
		return (0);
	if (!cpy_cmd_args(args + start, cmd_args)) //copia os argumentos do cmd(exceto pipes e redirs)
	{
		free_matrix(cmd_args);
		return (0);
	}
	if (!init_cmd_redir(cmd, args + start))
	{
		free_matrix(cmd_args);
		return (0);
	}
	cmd->args = cmd_args;
	return (1);
}

int	parse_n_init_cmd(t_minishell *sh, t_command **cmd, char **args) //Processa args para criar um array de t_command, lidando com comandos simples (sem pipes)
{
	int	cmd_count;

	if (!args || !args[0])
		return (0);
	cmd_count = count_pipes(args); //cmd_count armazena o numero de pipes que apareceram
	sh->total_pipeln_cmd = cmd_count; //aqui armazenamos a qnt em uma struct
	if (!init_cmd_arr(cmd, cmd_count)) //se falhar em alocar memoria para cmd
		return (0);
	if (cmd_count == 1) //se a qnt de pipe for 1
	{
		if (!parse_single_cmd(*cmd, args, 0)) //lida com comandos sem pipes
		{
			free(*cmd);
			return (0);
		}
		(*cmd)->piped = 0;
	}
	else
	{
		(*cmd)->piped = 1;
		if (!fill_cmd(args,*cmd))
		{
			free_cmd_struct(*cmd);
			free(*cmd);
			return (0);
		}
	}
	return (1);
}
