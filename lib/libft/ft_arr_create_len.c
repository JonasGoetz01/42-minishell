/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_create_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:48:25 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/03 18:43:23 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_create_len(size_t len)
{
	char	**arr;

	arr = ft_calloc(len, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[len - 1] = NULL;
	return (arr);
}
