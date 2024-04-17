/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:26:17 by jgotz             #+#    #+#             */
/*   Updated: 2024/04/16 12:05:35 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token;

	if (str == NULL && last_token == NULL)
		return (NULL);
	if (str != NULL)
		last_token = str;
	while (*last_token && ft_strchr(delim, *last_token))
		last_token++;
	if (!*last_token)
		return (NULL);
	token = last_token;
	while (*last_token && !ft_strchr(delim, *last_token))
		last_token++;
	if (*last_token)
		*last_token++ = '\0';
	return (token);
}
