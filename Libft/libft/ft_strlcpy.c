/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:53 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:47 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "libft.h"
=======
#include "../libft.h"
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[j] != '\0')
	{
		j++;
	}
	if (size == 0)
	{
		return (j);
	}
	while ((i < size - 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
			i++;
	}
	dst[i] = '\0';
	return (j);
}
