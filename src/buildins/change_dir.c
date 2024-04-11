#include "../../inc/minishell.h"

void	change_dir(char *path)
{
	if (chdir(path) != 0)
		printf("Could not change working directory\n");
}
