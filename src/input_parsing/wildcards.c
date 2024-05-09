/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:06:52 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 16:00:26 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_check_reverse(char *str, char **files)
{
	size_t	last_ind_str;
	size_t	last_ind_file;

	last_ind_str = ft_strlen(str) - 1;
	last_ind_file = ft_strlen(*files) - 1;
	while (str[last_ind_str] != '*')
	{
		if (str[last_ind_str] != (*files)[last_ind_file])
			return (false);
		if (last_ind_file == 0)
			break ;
		last_ind_str--;
		last_ind_file--;
	}
	return (true);
}

static void	ft_check(size_t *ind_str, size_t *ind_file, char *str, char **files)
{
	while ((*files)[*ind_file])
	{
		if ((*files)[*ind_file] == str[*ind_str])
			break ;
		(*ind_file)++;
	}
}

static bool	ft_check_file(size_t *ind_str, size_t *ind_file, char *str,
		char **files)
{
	while (str[*ind_str] || (*files)[*ind_file])
	{
		if (str[*ind_str] == '*')
		{
			while (str[(*ind_str)] == '*')
				(*ind_str)++;
			if (str[*ind_str] && ft_strnstr(&str[*ind_str], "*",
					ft_strlen(&str[*ind_str])) == 0)
				return (ft_check_reverse(str, files));
			else
				ft_check(ind_str, ind_file, str, files);
		}
		if (str[*ind_str] != (*files)[*ind_file])
			return (false);
		if (str[*ind_str] != 0)
			(*ind_str)++;
		if ((*files)[*ind_file] != 0)
			(*ind_file)++;
	}
	return (true);
}

static bool	ft_expand_wildcard_loop(char ***arr, char **files, char *str)
{
	size_t	ind_str;
	size_t	ind_file;
	char	*tmp;

	while (files && *files)
	{
		ind_str = 0;
		ind_file = 0;
		if (ft_check_file(&ind_str, &ind_file, str, files))
		{
			tmp = ft_strdup(*files);
			if (tmp == NULL || !ft_arr_add(tmp, arr))
				return (false);
		}
		files++;
	}
	return (true);
}

char	**ft_expand_wildcard(char *str)
{
	char	**files;
	char	**arr;
	bool	result;
	char	*tmp;

	arr = ft_arr_create();
	if (ft_strnstr(str, "*", ft_strlen(str)) == NULL)
	{
		tmp = ft_strdup(str);
		if (tmp == NULL || !ft_arr_add(tmp, &arr))
			return (ft_arr_free((void **)arr), NULL);
		return (arr);
	}
	files = ft_get_files(str[0] == '.');
	result = ft_expand_wildcard_loop(&arr, files, str);
	ft_arr_free((void **)files);
	if (!result)
		return (ft_arr_free((void **)arr), NULL);
	ft_arr_sort(arr);
	return (arr);
}
