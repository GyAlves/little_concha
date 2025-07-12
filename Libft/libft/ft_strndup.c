/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:51:46 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/12 16:52:14 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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