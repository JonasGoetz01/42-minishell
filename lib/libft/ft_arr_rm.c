/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:43:11 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/09 14:52:39 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_arr_rm(size_t ind, char ***arr)
{
	char	**new;
	size_t	len;
	char	*tmp;

	len = ft_arr_len(*arr);
	if (ind > len - 1)
		return (false);
	new = ft_arr_create_len(len);
	if (!new)
		return (false);
	tmp = (*arr)[ind];
	(*arr)[ind] = NULL;
	if (!ft_arr_cpy(*arr, new))
		return (free(new), (*arr)[ind] = tmp, false);
	if (!ft_arr_cpy(&((*arr)[ind + 1]), &(new[ind])))
		return (ft_arr_free((void **) new), (*arr)[ind] = tmp, false);
	new[len - 1] = NULL;
	(*arr)[ind] = tmp;
	ft_arr_free((void **) *arr);
	*arr = new;
	return (true);
}
