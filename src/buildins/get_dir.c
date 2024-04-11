#include "../../inc/minishell.h"

char	*get_current_dir(void)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	return (cwd);
}
