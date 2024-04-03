/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:14:03 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/03 14:41:16 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_arr_cpy(char **src, char **dst)
{
	size_t	ind;

	ind = 0;
	while (src[ind])
	{
		dst[ind] = ft_strdup(src[ind]);
		if (!dst[ind])
		{
			while (ind > 0)
				free(dst[--ind]);
			dst[0] = NULL;
			return (false);
		}
		ind++;
	}
	dst[ind] = 0;
	return (true);
}
