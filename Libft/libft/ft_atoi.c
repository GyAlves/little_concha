/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:30 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:17 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;
	int	result;

	n = 0;
	sign = 1;
	result = 0;
	while ((nptr[n] >= 9 && nptr[n] <= 13) || nptr[n] == 32)
		n++;
	if (nptr[n] == 45 || nptr[n] == 43)
	{
		if (nptr[n] == 45)
			sign = sign * -1;
		n++;
	}
	while (nptr[n] >= 48 && nptr[n] <= 57)
	{
		result = result * 10 + (nptr[n] - '0');
		n++;
	}
	return (result * sign);
}
