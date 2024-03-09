/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:20:29 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 14:32:18 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stack	*createStack(size_t capacity)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	stack->array = (t_token *)malloc(capacity * sizeof(t_token));
	if (stack->array == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	stack->capacity = capacity;
	stack->size = 0;
	return (stack);
}

void	push(t_stack *stack, t_token token)
{
	if (stack->size == stack->capacity)
	{
		stack->capacity *= 2;
		stack->array = (t_token *)realloc(stack->array, stack->capacity
				* sizeof(t_token));
		if (stack->array == NULL)
		{
			fprintf(stderr, "Memory allocation failed.\n");
			exit(EXIT_FAILURE);
		}
	}
	stack->array[stack->size++] = token;
}

t_token	pop(t_stack *stack)
{
	if (stack->size == 0)
	{
		fprintf(stderr, "Stack underflow.\n");
		exit(EXIT_FAILURE);
	}
	return (stack->array[--stack->size]);
}
