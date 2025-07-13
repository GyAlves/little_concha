#include "../../minishell.h"

t_redir_type	get_redir_type(char *str)
{
	if (!str)
		return (INVALID);
	if (!ft_strcmp(str, ">"))
		return (R_OUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<"))
		return (R_IN);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (INVALID);
}

int	is_pipe(char *str) //confere se é um pipe nos tokens 
{
	return (str && ft_strcmp(str, "|") == 0);
}

int	is_redir(char *str)
{
	return (get_redir_type(str) != INVALID);
}
