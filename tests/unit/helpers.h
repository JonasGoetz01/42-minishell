#ifndef HELPERS_H
# define HELPERS_H

# include "../../inc/minishell.h"
# include <stdarg.h>

t_token		**create_token_list(int count, ...);

void		free_token_list(t_token **head);

int			compare_ast_nodes(t_ast_node *node1, t_ast_node *node2);
t_ast_node	*create_ast(t_token **data);
void		add_left(t_ast_node **parent, t_token **data);
void		add_right(t_ast_node **parent, t_token **data);
void		free_ast(t_ast_node *root);
bool		compare_ast(t_ast_node **root1, t_ast_node **root2);

#endif