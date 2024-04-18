#include "helpers.h"

t_token	**create_token_list(int count, ...)
{
	va_list			args;
	t_token			**head;
	t_token			*current;
	char			*value;
	t_token			*token;
	t_token_type	type;

	va_start(args, count);
	head = malloc(sizeof(t_token));
	*head = NULL;
	current = NULL;
	for (int i = 0; i < count; ++i)
	{
		type = va_arg(args, t_token_type); // Get the type of the argument
		value = va_arg(args, char *);
		token = malloc(sizeof(t_token));
		if (!token)
			return (NULL);
		token->type = type; // Set the type of the token
		token->value = ft_strdup(value);
		token->next = NULL;
		if (!(*head))
		{
			*head = token;
			current = token;
		}
		else
		{
			current->next = token;
			current = current->next;
		}
	}
	va_end(args);
	return (head);
}

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(head);
}

int	compare_ast_nodes(t_ast_node *node1, t_ast_node *node2)
{
	if (node1 == NULL && node2 == NULL)
	{
		return (1);
	}
	if (node1 == NULL || node2 == NULL)
	{
		return (0);
	}
	if (node1->token->type != node2->token->type || strcmp(node1->token->value,
			node2->token->value) != 0)
	{
		return (0);
	}
	return (compare_ast_nodes(node1->left, node2->left)
		&& compare_ast_nodes(node1->right, node2->right));
}

t_ast_node	*create_ast(t_token **data)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->token = create_token((*data)->type, (*data)->value);
	if (node->token->value != (*data)->value)
		return (free(node), NULL);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	add_left(t_ast_node **parent, t_token **data)
{
	if (!parent)
		return ;
	(*parent)->left = create_ast(data);
}

void	add_right(t_ast_node **parent, t_token **data)
{
	if (!parent)
		return ;
	(*parent)->right = create_ast(data);
}

void	free_ast(t_ast_node *root)
{
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
}

bool	compare_ast(t_ast_node **root1, t_ast_node **root2)
{
	// If both roots are NULL, they are equal
	if (!*root1 && !*root2)
	{
		return (true);
	}
	// If only one root is NULL, they are not equal
	if (!*root1 || !*root2)
	{
		return (false);
	}
	// If data of the roots are not equal, they are not equal
	if ((*root1)->token->type != (*root2)->token->type)
	{
		return (false);
	}
	root1 = &(*root1)->left;
	root2 = &(*root2)->left;
	// Recursively compare left and right children
	return (compare_ast(root1, root2) && compare_ast(root1, root2));
}
