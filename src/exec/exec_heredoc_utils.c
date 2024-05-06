#include "../../inc/minishell.h"

void	ft_error_heredoc(char *limiter)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin("here-document at line 1 \
			delimited by end-of-file (wanted `", limiter);
	if (tmp == NULL)
		return ;
	msg = ft_strjoin(tmp, "')");
	if (msg == NULL)
		return (free(tmp));
	ft_print_error(msg, "warning");
	free(msg);
}
