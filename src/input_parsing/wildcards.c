#include "../../inc/minishell.h"
#include <dirent.h>

static char	**ft_get_files(void)
{
	DIR				*dir;
	struct dirent	*dir_struct;
	char			**arr;

	dir = opendir("./");
	if (dir == NULL)
		return (NULL);
	arr = ft_arr_create();
	dir_struct = readdir(dir);
	while (dir_struct)
	{
		if (dir_struct->d_type == DT_REG || dir_struct->d_type == DT_DIR)
		{
			if (ft_strncmp(dir_struct->d_name, ".", 1) != 0 && ft_strncmp(dir_struct->d_name, "..", 3) != 0)
			{
				if (!ft_arr_add(ft_strdup(dir_struct->d_name), &arr))
					return (closedir(dir), ft_arr_free((void **) arr), NULL);
			}
		}
		dir_struct = readdir(dir);
	}
	closedir(dir);
	return (arr);
}

static bool ft_check_reverse(char *str, char **files)
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

static bool	ft_check_file(size_t *ind_str, size_t *ind_file, char *str, char **files)
{
	while (str[*ind_str] || (*files)[*ind_file])
	{
		if (str[*ind_str] == '*')
		{
			while (str[(*ind_str)] == '*')
				(*ind_str)++;
			if (str[*ind_str] && ft_strnstr(&str[*ind_str], "*", ft_strlen(&str[*ind_str])) == 0)
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

	while (files && *files)
	{
		ind_str = 0;
		ind_file = 0;
		if (ft_check_file(&ind_str, &ind_file, str, files))
		{
			if (!ft_arr_add(ft_strdup(*files), arr))
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

	arr = ft_arr_create();
	if (ft_strnstr(str, "*", ft_strlen(str)) == NULL)
	{
		if (!ft_arr_add(ft_strdup(str), &arr))
			return (ft_arr_free((void **) arr), NULL);
		return (arr);
	}
	files = ft_get_files();
	result = ft_expand_wildcard_loop(&arr, files, str);
	ft_arr_free((void **) files);
	if (!result)
		return (ft_arr_free((void **) arr), NULL);
	ft_arr_sort(arr);
	return (arr);
}
