/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:00:18 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/03 14:48:32 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_add(char *str, char **arr)
{
	char	**new;
	size_t	len;

	len = ft_arr_len(arr);
	new = ft_arr_create_len(len + 2);
	if (!new)
		return (NULL);
	if (!ft_arr_cpy(arr, new))
	{
		free(new);
		return (NULL);
	}
	new[len] = str;
	new[len + 1] = NULL;
	return (new);
}
