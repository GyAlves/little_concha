/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:20:30 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:58 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
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
