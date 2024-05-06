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

char	*ft_test_compatible_readline(t_global *global)
{
	char	*line;
	char	*tmp;

	if (global->isatty)
		return (readline("> "));
	else
	{
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strtrim(line, "\n");
		if (tmp == NULL)
			free(line);
		return (tmp);
	}
}
