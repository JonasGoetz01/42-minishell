#include "../../inc/minishell.h"
#include <dirent.h>

char	**ft_get_files(bool with_hidden)
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
			if (with_hidden || (ft_strncmp(dir_struct->d_name, ".", 1) != 0 && ft_strncmp(dir_struct->d_name, "..", 3) != 0))
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
