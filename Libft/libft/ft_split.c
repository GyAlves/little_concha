/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:18:22 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:34 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char separator)
{
	int	count;
	int	index;
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	count = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != (unsigned char)separator)
		{
			while (str[index] != (unsigned char)separator && str[index] != '\0')
				index++;
			count++;
		}
		if (str[index] != '\0')
			index++;
	}
	return (count);
}

static int	free_memory(char ***str_list, int allocated)
{
	int	index;

	if (!str_list || !*str_list)
		return (0);
	index = 0;
	while (index < allocated)
	{
		free((*str_list)[index]);
		index++;
	}
	free(*str_list);
	*str_list = NULL;
	return (0);
}

static int	fill_arr(int size, const char *str, char c, char ***str_list)
{
	int		counter;
	int		index;
	int		pass;
	char	*test;

	index = 0;
	counter = 0;
	while (str[index] != '\0' && counter < size)
	{
		pass = 0;
		while (str[index] == (unsigned char)c)
			index++;
		while (str[index + pass] && str[index + pass] != c)
			pass++;
		test = ft_substr(&str[index], 0, pass);
		if (!test)
			return (free_memory(str_list, counter));
		(*str_list)[counter] = test;
		counter++;
		index += pass;
	}
	(*str_list)[size] = NULL;
	return (1);
}

char	**ft_split(char const *str, char separator)
{
	int		size;
	char	**str_list;

	if (!str)
		return (ft_calloc(1, sizeof(char *)));
	size = count_words(str, separator);
	if (size == 0)
		return (ft_calloc(1, sizeof(char *)));
	str_list = (char **) ft_calloc((size + 1), sizeof(char *));
	if (str_list == 0)
		return (0);
	if (!fill_arr(size, str, separator, &str_list))
	{
		free(str_list);
		return (NULL);
	}
	return (str_list);
}
