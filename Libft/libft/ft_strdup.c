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

<<<<<<< HEAD
#include "libft.h"
=======
#include "../libft.h"
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

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
