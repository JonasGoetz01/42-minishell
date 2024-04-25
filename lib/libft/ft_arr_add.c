/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:00:18 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/25 13:15:14 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_arr_add(char *str, char ***arr)
{
	char	**new;
	size_t	len;

	len = ft_arr_len(*arr);
	new = ft_arr_create_len(len + 2);
	if (!new)
		return (false);
	if (!ft_arr_cpy(*arr, new))
	{
		free(new);
		return (false);
	}
	new[len] = str;
	new[len + 1] = NULL;
	ft_arr_free((void **) *arr);
	*arr = new;
	return (true);
}
