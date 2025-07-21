#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*verificate_valid_answer;

	if (!s1 || !set)
		return (ft_calloc(1, sizeof(char)));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	verificate_valid_answer = ft_substr(s1, start, end - start);
	if (!verificate_valid_answer)
		return (ft_calloc(1, sizeof(char)));
	return (verificate_valid_answer);
}
