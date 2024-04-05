#include "../../inc/minishell.h"

char	*get_hostname(void)
{
	return (ft_split(execute_command("/bin/hostname"), '\n')[0]);
}
