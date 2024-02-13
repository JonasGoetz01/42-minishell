/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:54:28 by jgotz             #+#    #+#             */
/*   Updated: 2023/10/10 09:25:41 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t length)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (!s && !d)
		return (NULL);
	if (s < d)
	{
		s += length;
		d += length;
		while (length--)
			*(--d) = *(--s);
	}
	else
	{
		while (length--)
			*(d++) = *(s++);
	}
	return (dest);
}
