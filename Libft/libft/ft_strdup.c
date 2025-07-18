/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:02 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:41 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
