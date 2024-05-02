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
			if (ft_strncmp(dir_struct->d_name, ".", 2) != 0 && ft_strncmp(dir_struct->d_name, "..", 3) != 0)
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

char	**ft_expand_wildcard(char *str)
{
	size_t	ind_str;
	size_t	ind_file;
	char	**files;
	char	**files_start;
	char	**arr;

	arr = ft_arr_create();
	if (ft_strnstr(str, "*", ft_strlen(str)) == NULL)
		return (NULL);
	files = ft_get_files();
	files_start = files;
	while (files && *files)
	{
		ind_str = 0;
		ind_file = 0;
		while (str[ind_str] && (*files)[ind_file])
		{
			if (str[ind_str] == '*')
			{
				ind_str++;
				while ((*files)[ind_file])
				{
					if ((*files)[ind_file] == str[ind_str])
						break ;
					ind_file++;
				}
				if ((*files)[ind_file] != str[ind_str])
					break ;
			}
			else if (str[ind_str] != (*files)[ind_file])
				break ;
			else
			{
				ind_str++;
				ind_file++;
			}
		}
		if (str[ind_str] == 0 && (*files)[ind_file] == 0)
		{
			if (!ft_arr_add(ft_strdup(*files), &arr))
				return (ft_arr_free((void **) files), ft_arr_free((void **) arr), NULL);
		}
		files++;
	}
	ft_arr_free((void **) files_start);
	return (arr);
}

int	main(int argc, char **argv)
{
	char **files;
	char	**temp;

	files = ft_expand_wildcard(argv[1]);
	temp = files;
	while (files && *files)
	{
		printf("%s\n", *files);
		files++;
	}
	ft_arr_free((void **) temp);
}
