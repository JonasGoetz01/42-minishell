/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:54:28 by jgotz             #+#    #+#             */
/*   Updated: 2023/10/09 14:15:17 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	const char	*s;
	const char	*t;

	if (*to_find == '\0')
	{
		return ((char *)str);
	}
	while (*str && len > 0)
	{
		s = str;
		t = to_find;
		while (*s && *t && (*s == *t))
		{
			s++;
			t++;
		}
		if (*t == '\0')
		{
			if (ft_strlen(to_find) <= len)
				return ((char *)str);
		}
		str++;
		len--;
	}
	return (NULL);
}

/* #include <stdio.h>

int	main(void)
{
	char haystack[30] = "aaabcabcd";
	printf("%s", ft_strnstr(haystack, "cd", 8));
} */
