#include "../../minishell.h"

size_t	ft_arrlen(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}
