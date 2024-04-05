#include "../../inc/minishell.h"

t_stack	*create_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		// Handle memory allocation error
		exit(EXIT_FAILURE);
	}
	stack->top = NULL;
	return (stack);
}

void	stack_push(t_stack *stack, t_token token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		// Handle memory allocation error
		exit(EXIT_FAILURE);
	}
	new_token->type = token.type;
	new_token->value = token.value;
	new_token->next = stack->top;
	stack->top = new_token;
}

t_token	stack_pop(t_stack *stack)
{
	t_token	popped_token;
	t_token	*temp;

	if (stack->top == NULL)
	{
		// Handle empty stack error
		exit(EXIT_FAILURE);
	}
	popped_token = *(stack->top);
	temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
	return (popped_token);
}

t_token	stack_peek(t_stack *stack)
{
	if (stack->top == NULL)
	{
		// Handle empty stack error
		exit(EXIT_FAILURE);
	}
	return (*(stack->top));
}

int	stack_is_not_empty(t_stack *stack)
{
	return (stack->top != NULL);
}
