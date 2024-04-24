#include "../../inc/minishell.h"

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
	highest_token_brackets_level = 0;
	current_token = tokens;
	ast = *root;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_BRACKET_L)
			brackets_level++;
		else if (current_token->type == TOKEN_BRACKET_R)
			brackets_level--;
		if (highest_token == NULL
			|| precedence(*current_token) > precedence(*highest_token)
			|| (precedence(*current_token) == precedence(*highest_token)
				&& brackets_level <= highest_token_brackets_level))
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
		ast->file_in = NULL;
		ast->fd_in[0] = NULL;
		ast->fd_in[1] = NULL;
		ast->fd_out[0] = NULL;
		ast->fd_out[1] = NULL;
		ast->file_out = NULL;
		ast->exit_status = -1;
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
	if (highest_token->next == NULL)
		return ;
	left_arm = tokens;
	current_token = tokens;
	while (current_token->next && current_token->next != highest_token)
		current_token = current_token->next;
	current_token->next = NULL;
	right_arm = highest_token->next;
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
	if (DEBUG)
	{
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
}
