#include "../../minishell.h"

int	ft_isalnum(int c)
{
	return ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || \
		(c >= 97 && c <= 122));
}
