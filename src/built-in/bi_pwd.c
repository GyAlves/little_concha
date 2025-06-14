#include "../../minishell.h"

void	bi_pwd(t_minishell *ms)
{
	char	*cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		ms->exit_status = 1;
		return ;
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	ms->exit_status = 0;
}
