/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:11 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/26 15:41:57 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_arr_rm(size_t ind, char ***arr)
{
	char	**new;
	size_t	len;

	len = ft_arr_len(*arr);
	if (ind > len - 1)
		return (false);
	new = ft_arr_create_len(len);
	if (!new)
		return (false);
	(*arr)[ind] = NULL;
	if (!ft_arr_cpy(*arr, new))
	{
		free(new);
		return (false);
	}
	if (!ft_arr_cpy(&((*arr)[ind + 1]), &(new[ind])))
	{
		ft_arr_free((void **) new);
		return (false);
	}
	new[len - 1] = NULL;
	ft_arr_free((void **) *arr);
	*arr = new;
	return (true);
}
