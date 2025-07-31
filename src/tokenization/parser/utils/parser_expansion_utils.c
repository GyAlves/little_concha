#include "minishell.h"
#include <ctype.h>

char	*join_and_free(char *result, char *to_add)
{
	char	*temp;

	temp = ft_strjoin(result, to_add);
	free(result);
	free(to_add);
	return (temp);
}
