#include "../../inc/minishell.h"

// t_ast_node	*create_ast_node(int type, char *value)
// {
// 	t_ast_node	*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (node != NULL)
// 	{
// 		node->type = type;
// 		node->value = strdup(value);
// 		node->left = NULL;
// 		node->right = NULL;
// 	}
// 	return (node);
// }

// t_ast_node	*parse_tokens_to_ast(t_token *tokens)
// {
// 	t_ast_node	*root;
// 	t_ast_node	*current_node;
// 	t_token		*current_token;
// 	t_ast_node	*new_node;
// 	int			current_precedence;

// 	root = NULL;
// 	current_node = NULL;
// 	current_token = tokens;
// 	while (current_token != NULL)
// 	{
// 		new_node = create_ast_node(current_token->type, current_token->value);
// 		current_precedence = precedence(*current_token);
// 		if (root == NULL || current_precedence > precedence_node(root))
// 			root = new_node;
// 		else
// 		{
// 			current_node = root;
// 			while (current_node->right != NULL
// 				&& current_precedence <= precedence_node(current_node->right))
// 				current_node = current_node->right;
// 			new_node->left = current_node->right;
// 			current_node->right = new_node;
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (root);
// }

// void	print_ast_execution_order(t_ast_node *root)
// {
// 	if (root == NULL)
// 	{
// 		return ;
// 	}
// 	printf("%s\n", root->value);
// 	print_ast_execution_order(root->left);
// 	print_ast_execution_order(root->right);
// }

// length of the token
// figures out the length of the token by checking for delimiters
int	token_length(const char *input, const char *delimiters)
{
	int	length;

	length = 0;
	while (input[length] != '\0' && !ft_strchr(delimiters, input[length]))
	{
		length++;
	}
	return (length);
}

t_token	*tokenize(const char *input)
{
	t_token			*tokens;
	t_token			*current;
	const char		*delimiters = "+-*/()<>|&\"'; ";
	char			*value;
	t_token_type	type;
	t_token			*new_token;
	int				i;
	int				tokenLen;

	tokens = NULL;
	current = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr(delimiters, input[i]))
		{
			value = ft_substr(input, i, 1);
			if (input[i] == '(')
				type = TOKEN_BRACKET_L;
			else if (input[i] == ')')
				type = TOKEN_BRACKET_R;
			else if (input[i] == '<')
			{
				if (input[i + 1] == '<')
				{
					type = TOKEN_DOUBLE_LESS;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_LESS;
			}
			else if (input[i] == '>')
			{
				if (input[i + 1] == '>')
				{
					type = TOKEN_DOUBLE_GREATER;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_GREATER;
			}
			else if (input[i] == '|')
			{
				if (input[i + 1] == '|')
				{
					type = TOKEN_DOUBLE_PIPE;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_PIPE;
			}
			else if (input[i] == '&')
			{
				if (input[i + 1] == '&')
				{
					type = TOKEN_DOUBLE_AMPERSAND;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_AMPERSAND;
			}
			else if (input[i] == '\"')
			{
				type = TOKEN_DOUBLE_QUOTE;
				value = ft_substr(input, i, 1);
				// Include the double quote in the value
			}
			else if (input[i] == '\'')
			{
				type = TOKEN_SINGLE_QUOTE;
				value = ft_substr(input, i, 1);
				// Include the single quote in the value
			}
			else if (input[i] == ';')
				type = TOKEN_SEMICOLON;
			else
				type = TOKEN_WORD;
			new_token = create_token(type, value);
			append_token(&tokens, new_token);
			i++; // Increment i since we've already processed this character
		}
		else
		{
			tokenLen = token_length(input + i, delimiters);
			value = ft_substr(input, i, tokenLen);
			new_token = create_token(TOKEN_WORD, value);
			append_token(&tokens, new_token);
			i += tokenLen; // Increment i by token length
		}
	}
	return (tokens);
}

//
// Spaces should only stay there if they are after a quote or double quote
void	remove_unused_spaces(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*old;
	t_token	*prev;

	prev = NULL;
	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE)
		{
			while (next != NULL && next->type != current->type)
				next = next->next;
		}
		else if (current->type == TOKEN_WORD && ft_strchr(current->value, ' '))
		{
			old = current;
			current = next;
			free(old->value);
			free(old);
			if (prev == NULL)
				*tokens = current;
			else
				prev->next = current;
		}
		prev = current;
		current = next;
	}
}

void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens != NULL)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

int	isOperator(t_token token)
{
	return (token.type == TOKEN_AMPERSAND || token.type == TOKEN_BRACKET_L
		|| token.type == TOKEN_BRACKET_R || token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_DOUBLE_GREATER || token.type == TOKEN_DOUBLE_LESS
		|| token.type == TOKEN_DOUBLE_PIPE || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS || token.type == TOKEN_PIPE
		|| token.type == TOKEN_SEMICOLON);
}

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
	if (token.type == TOKEN_BRACKET_L || token.type == TOKEN_BRACKET_R)
		return (0);
	else if (token.type == TOKEN_DOUBLE_GREATER
		|| token.type == TOKEN_DOUBLE_LESS || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS)
		return (1);
	else if (token.type == TOKEN_DOUBLE_PIPE || token.type == TOKEN_PIPE)
		return (2);
	else if (token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_AMPERSAND)
		return (3);
	else
		return (-1);
}

int	precedence_node(t_ast_node *node)
{
	return (precedence(*create_token(node->token->type, node->token->value)));
}

t_token	*postfixFromTokens(t_token *tokens)
{
	t_token	*current_token;
	t_stack	*stack;
	t_token	*output_queue;
	int		in_single_quote;
	int		in_double_quote;

	stack = create_stack();
	output_queue = NULL;
	current_token = tokens;
	in_single_quote = 0;
	in_double_quote = 0;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD
			|| current_token->type == TOKEN_SINGLE_QUOTE
			|| current_token->type == TOKEN_DOUBLE_QUOTE)
		{
			if (current_token->type == TOKEN_SINGLE_QUOTE)
			{
				if (in_double_quote == 1)
					append_token(&output_queue,
						create_token(current_token->type,
							current_token->value));
				else
					in_single_quote = !in_single_quote;
			}
			if (current_token->type == TOKEN_DOUBLE_QUOTE)
			{
				if (in_single_quote == 1)
					append_token(&output_queue,
						create_token(current_token->type,
							current_token->value));
				else
					in_double_quote = !in_double_quote;
			}
			if (current_token->type == TOKEN_WORD)
			{
				if (current_token->value[0] == '\\')
				{
					if (current_token->next)
						current_token = current_token->next;
					else
						break ;
				}
				append_token(&output_queue, create_token(current_token->type,
						current_token->value));
			}
		}
		else if (isOperator(*current_token))
		{
			while (stack_is_not_empty(stack)
				&& precedence(stack_peek(stack)) >= precedence(*current_token))
			{
				append_token(&output_queue, create_token(stack_peek(stack).type,
						stack_pop(stack).value));
			}
			stack_push(stack, *current_token);
		}
		else if (current_token->type == TOKEN_BRACKET_L)
		{
			stack_push(stack, *current_token);
		}
		else if (current_token->type == TOKEN_BRACKET_R)
		{
			while (stack_is_not_empty(stack)
				&& stack_peek(stack).type != TOKEN_BRACKET_L)
			{
				append_token(&output_queue, create_token(stack_peek(stack).type,
						stack_pop(stack).value));
			}
			stack_pop(stack);
		}
		current_token = current_token->next;
	}
	while (stack_is_not_empty(stack))
	{
		append_token(&output_queue, create_token(stack_peek(stack).type,
				stack_pop(stack).value));
	}
	free(stack->top);
	free(stack);
	return (output_queue);
}

// walk through tokens and search for the highest precedence operator
// -> use precedence_node for that
// set the root of the ast to that operator
// walk through tokens again and set the left and right nodes of the root recursively
void	gen_ast(t_ast_node **root, t_token *tokens)
{
	t_token		*highest_token;
	t_token		*current_token;
	t_ast_node	*ast;
	t_token		*left_arm;
	t_token		*right_arm;

	highest_token = NULL;
	current_token = tokens;
	ast = *root;
	while (current_token != NULL)
	{
		if (highest_token == NULL
			|| precedence(*current_token) > precedence(*highest_token))
			highest_token = current_token;
		current_token = current_token->next;
	}
	if (ast == NULL)
	{
		ast = malloc(sizeof(t_ast_node));
		//@TODO: Check if malloc failed
		ast->token = highest_token;
		ast->left = NULL;
		ast->right = NULL;
		ast->fd_in = -1;
		ast->fd_out = -1;
		*root = ast;
	}
	if (highest_token->type != TOKEN_WORD)
	{
		left_arm = tokens;
		right_arm = highest_token->next;
		current_token = tokens;
		while (current_token->next != highest_token)
			current_token = current_token->next;
		current_token->next = NULL;
		ast->token->next = NULL;
		gen_ast(&(ast->left), left_arm);
		gen_ast(&(ast->right), right_arm);
	}
}

void	print_ast(t_ast_node **root, int level)
{
	t_ast_node	*ast;

	ast = *root;
	if (ast == NULL)
		return ;
	print_ast(&(ast->right), level + 1);
	while (ast->token != NULL)
	{
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("Type: %d, Value: %s\n", ast->token->type, ast->token->value);
		ast->token = ast->token->next;
	}
	print_ast(&(ast->left), level + 1);
}
