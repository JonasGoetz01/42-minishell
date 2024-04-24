#include "../../inc/minishell.h"

// Prio A:
// Parentheses ()
// Prio B:
// Redirection >, <, >>, <<
// Prio C:
// Pipe |
// Prio D:
// Logical AND && and Logical OR ||
int	precedence(t_token token)
{
	if (token.type == TOKEN_WORD)
		return (1);
	else if (token.type == TOKEN_BRACKET_L || token.type == TOKEN_BRACKET_R)
		return (0);
	else if (token.type == TOKEN_DOUBLE_GREATER
		|| token.type == TOKEN_DOUBLE_LESS || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS)
		return (2);
	else if (token.type == TOKEN_PIPE)
		return (3);
	else if (token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_DOUBLE_PIPE)
		return (4);
	else
		return (-1);
}

int	precedence_node(t_ast_node *node)
{
	return (precedence(*create_token(node->token->type, node->token->value)));
}
