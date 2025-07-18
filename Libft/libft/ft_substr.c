/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:20:41 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:59 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_memory(size_t len)
{
	char	*buffer;

	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*buffer;
	size_t	index;

	if (!s)
		return (ft_calloc(1, sizeof(char)));
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > len_s)
		len = len_s - start;
	index = 0;
	buffer = allocate_memory(len);
	if (!buffer)
		return (NULL);
	while (index < len)
	{
		buffer[index] = s[start];
		index++;
		start++;
	}
	buffer[index] = '\0';
	return (buffer);
}
