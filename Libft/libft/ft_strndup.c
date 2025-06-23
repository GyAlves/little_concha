#include "../../minishell.h"

char	*strndup(const char *s, size_t n)
{
	char	*scopy;
	size_t	len;

	len = 0;
	while (s[len] && len < n)
		len++;
	scopy = (char *)malloc(sizeof(char) * (len + 1));
	if (!scopy)
		return (NULL);
	ft_strlcpy(scopy, s, len + 1);
	return (scopy);
}
