/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:20:29 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/11 20:10:15 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stack	*createStack(size_t capacity)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack != NULL)
	{
		stack->array = (t_token *)malloc(capacity * sizeof(t_token));
		if (stack->array != NULL)
		{
			stack->capacity = capacity;
			stack->size = 0;
		}
		else
		{
			free(stack);
			stack = NULL;
		}
	}
	return (stack);
}

void	push(t_stack *stack, t_token token)
{
	if (stack->size < stack->capacity)
	{
		stack->array[stack->size++] = token;
	}
	else
	{
		fprintf(stderr, "Stack overflow.\n");
	}
}

t_token	pop(t_stack *stack)
{
		t_token dummy_token;

	if (stack->size > 0)
	{
		return (stack->array[--stack->size]);
	}
	else
	{
		fprintf(stderr, "Stack underflow.\n");
		// Return a dummy token to indicate error
		dummy_token.type = -1; // Some invalid token type
		return (dummy_token);
	}
}

t_token	peek(const t_stack *stack)
{
		t_token dummy_token;

	if (stack->size > 0)
	{
		return (stack->array[stack->size - 1]);
	}
	else
	{
		fprintf(stderr, "Stack is empty.\n");
		// Return a dummy token to indicate error
		dummy_token.type = -1; // Some invalid token type
		return (dummy_token);
	}
}

void	freeStack(t_stack *stack)
{
	free(stack->array);
	free(stack);
}
