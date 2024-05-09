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
	free(tmp);
	if (msg == NULL)
		return ;
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

char	*ft_get_limiter(t_ast_node *node)
{
	t_token	*token;

	token = ft_get_file_token(node);
	if (token == NULL)
		return (NULL);
	if (token->be_value)
		return (token->be_value);
	else
		return (token->value);
}
