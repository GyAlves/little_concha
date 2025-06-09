#include "../../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*scpy;
	size_t	len;

	len = (ft_strlen(s) + 1);
	scpy = (char *)malloc ((sizeof(char)) * (len));
	if (!scpy)
		return (NULL);
	ft_strlcpy(scpy, s, len);
	return (scpy);
}