#include "../../inc/minishell.h"
#include <dirent.h>

static char	**ft_get_files(void)
{
	DIR	dir;

	dir = opendir("./");
}

char	*ft_expand_wildcard(char *str)
{
	size_t	ind;
	char	*str_asterix;
	size_t	ind_asterix;

	ind = 0;
	while (str[ind])
	{
		str_asterix = ft_strnstr(str, "*", ft_strlen(str));
		if (str_asterix == NULL)
			return (NULL);
		ind_asterix = str_asterix - str;

	}
}
