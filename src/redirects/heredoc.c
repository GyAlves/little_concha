#include "../../minishell.h"

//heredoc permite passar a STDIN diretamente no terminal até uma palavra delimitadora ex: cat << FNSH
//criar um input temporario, a partir de STDIN
//vamos:
// detectar '<<' \/
//detectar o delimitador FNSH \/
//escrever até o delimitador ser encontrado \/
//criar um arquivo temporario
//salvar as linhas em um arquivo temporario

static int	write_till_delimiter(int fd, char *delimiter, char **envp)
{
	char	*line;
	char	*expanded;

	while (6)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				free(line);
			return (1);
		}
		expanded = replace_variables(NULL, line);
		free(line);
		if (!expanded)
			return (0);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	return (0);
}
