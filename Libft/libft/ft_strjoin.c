#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	l1;
	size_t	l2;
	size_t	t_len;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	t_len = l1 + l2 + 1;
	strjoin = malloc ((sizeof(char)) * (t_len));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, l1);
	ft_memcpy(strjoin + l1, s2, l2);
	strjoin[l1 + l2] = '\0';
	return (strjoin);
}
