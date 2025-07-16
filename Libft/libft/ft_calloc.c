/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:44 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/16 11:43:53 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			length;
	void			*buffer;
	unsigned char	*ptr;
	size_t			index;

	index = 0;
	if (nmemb != 0 && size > (size_t) - 1 / nmemb)
		return (NULL);
	length = nmemb * size;
	buffer = malloc(length);
	if (!buffer)
		return (NULL);
	ptr = (unsigned char *)buffer;
	while (index < length)
	{
		ptr[index] = 0;
		index++;
	}
	return (buffer);
}
