#include "../../inc/minishell.h"

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
	const char		*delimiters = "()<>|&\"' $";
	char			*value;
	t_token_type	type;
	t_token			*new_token;
	int				i;
	int				tokenLen;

	tokens = NULL;
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

// Print the tokens
void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens != NULL)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

// Check if the token is an operator
int	isOperator(t_token token)
{
	return (token.type == TOKEN_AMPERSAND || token.type == TOKEN_BRACKET_L
		|| token.type == TOKEN_BRACKET_R || token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_DOUBLE_GREATER || token.type == TOKEN_DOUBLE_LESS
		|| token.type == TOKEN_DOUBLE_PIPE || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS || token.type == TOKEN_PIPE);
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
	int			highest_token_brackets_level;
	int			brackets_level;
	t_token		*prev_token;

	highest_token = NULL;
	brackets_level = 0;
	current_token = tokens;
	ast = *root;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_BRACKET_L)
			brackets_level++;
		else if (current_token->type == TOKEN_BRACKET_R)
			brackets_level--;
		if (highest_token == NULL || (brackets_level == 0
				&& precedence(*current_token) >= precedence(*highest_token))
			|| (brackets_level > 0
				&& precedence(*current_token) > precedence(*highest_token))
			|| highest_token->type == TOKEN_BRACKET_L
			|| highest_token->type == TOKEN_BRACKET_R)
		{
			highest_token = current_token;
			highest_token_brackets_level = brackets_level;
		}
		current_token = current_token->next;
	}
	if (DEBUG)
		printf("Highest token: %s\nHighest Bracket Level: %d\n",
			highest_token->value, highest_token_brackets_level);
	if (ast == NULL)
	{
		ast = malloc(sizeof(t_ast_node));
		//@TODO: Check if malloc failed
		ast->token = highest_token;
		ast->process = NULL;
		ast->left = NULL;
		ast->right = NULL;
		ast->fd_in[0] = -1;
		ast->fd_in[1] = -1;
		ast->fd_out[0] = -1;
		ast->fd_out[1] = -1;
		*root = ast;
	}
	if (highest_token->type == TOKEN_WORD)
	{
		ast->token = tokens;
		while (ast->token->type == TOKEN_BRACKET_L
			|| ast->token->type == TOKEN_BRACKET_R)
			ast->token = ast->token->next;
		current_token = ast->token;
		while (current_token->next != NULL)
			current_token = current_token->next;
		while (current_token->type == TOKEN_BRACKET_L
			|| current_token->type == TOKEN_BRACKET_R)
		{
			prev_token = ast->token;
			while (prev_token->next != current_token)
				prev_token = prev_token->next;
			prev_token->next = NULL;
			free(current_token);
			current_token = prev_token;
		}
		return ;
	}
	left_arm = tokens;
	current_token = tokens;
	while (current_token->next != highest_token)
		current_token = current_token->next;
	current_token->next = NULL; // Terminate the left arm here
	right_arm = highest_token->next;
	// Assign the right arm from the token after the highest token
	ast->token->next = NULL;
	gen_ast(&(ast->left), left_arm);
	gen_ast(&(ast->right), right_arm);
}

void	print_ast(t_ast_node **root, int level)
{
	t_ast_node	*ast;
	t_token		*token;

	ast = *root;
	if (ast == NULL)
		return ;
	print_ast(&(ast->right), level + 1);
	token = ast->token;
	while (token != NULL)
	{
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("Type: %d, Value: %s Prio: %d\n", token->type, token->value,
			precedence_node(ast));
		token = token->next;
	}
	print_ast(&(ast->left), level + 1);
}

// sometimes the tokens need to be rearranged
// example 1:
// echo < file.txt hello ... => echo hello ... < file.txt
// example 2:
// echo < file.txt hello ... && test => echo hello ... < file.txt && test
// example 3:
// < file.txt echo hello ... => echo hello ... < file.txt
// example 4:
// < file.txt echo hello ... && test => echo hello ... < file.txt && test
//
// For testing
// echo 1 && < test.txt echo 2 && echo 3
// echo 1 && < test.txt echo 2 && < test1.txt echo 3
// < test.txt echo 1
void	rearrange_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*redirect;
	t_token	*file;
	t_token	*after_file;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	// Find the first redirection token
	while (current != NULL && !(current->type == TOKEN_LESS
			|| current->type == TOKEN_DOUBLE_LESS
			|| current->type == TOKEN_GREATER
			|| current->type == TOKEN_DOUBLE_GREATER))
	{
		prev = current;
		current = current->next;
	}
	// If < is the first token
	if (prev == NULL)
	{
		redirect = *tokens;
		file = redirect->next;
		after_file = file->next;
		current = after_file;
		*tokens = after_file;
		while (current != NULL && current->type == TOKEN_WORD)
			current = current->next;
		while (after_file != NULL && after_file->next != NULL
			&& after_file->next->type == TOKEN_WORD)
			after_file = after_file->next;
		file->next = after_file->next;
		after_file->next = redirect;
		if (file->next != NULL)
			rearrange_tokens(&file->next);
	}
	// If < is not the first token
	else if (current != NULL && (prev == NULL || prev->type != TOKEN_WORD))
	{
		// Handle case where redirection token is not the first token
		redirect = current;
		file = current->next;
		after_file = file->next;
		current = after_file;
		while (current != NULL && current->type == TOKEN_WORD)
			current = current->next;
		if (prev != NULL)
			prev->next = after_file;
		else
			(*tokens)->next = after_file;
		while (after_file != NULL && after_file->next != NULL
			&& after_file->next->type == TOKEN_WORD)
			after_file = after_file->next;
		file->next = after_file->next;
		after_file->next = redirect;
		if (file->next != NULL)
			rearrange_tokens(&file->next);
	}
}

void	combine_words_in_quotes(t_token **tokens)
{
	t_token			*current;
	int				num_tokens;
	t_token_type	type;
	t_token			*start;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE)
		{
			num_tokens = 0;
			type = current->type;
			start = current;
			while (current->next && current->next->type != type)
			{
				current = current->next;
				num_tokens++;
			}
			if (current->next == NULL)
			{
				printf("Unmatched quote\n");
				return ;
			}
			printf("Num tokens: %d\n", num_tokens);
			current = start;
			current = current->next;
			num_tokens--;
			current->value = ft_strjoin(current->value, "");
			while (num_tokens > 0)
			{
				current->value = ft_strjoin(current->value,
						current->next->value);
				if (current->next->next)
					current->next = current->next->next;
				else
					current->next = NULL;
				num_tokens--;
			}
		}
		current = current->next;
	}
}
