/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:54:28 by jgotz             #+#    #+#             */
/*   Updated: 2023/10/10 09:46:39 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last_match;

	last_match = NULL;
	while (*str)
	{
		if (*str == (char)c)
			last_match = (char *)str;
		str++;
	}
	if ((char)c == '\0')
	{
		last_match = (char *)str;
	}
	return (last_match);
}
