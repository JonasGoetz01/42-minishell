#include "../../inc/minishell.h"

void	ft_open_in_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->file_in = fd;
}

void	ft_open_out_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->file_out = fd;
}

void	ft_open_out_append_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->file_out = fd;
}
