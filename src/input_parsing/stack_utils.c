/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:20:29 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 13:39:45 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	stack_len(t_stack *stack)
{
	int		i;
	t_stack	*current;

	if (stack == NULL || stack->value == NULL)
		return (0);
	i = 0;
	current = stack;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/// removes the last element of a  stack and returns it.
t_stack	*pop(t_stack *stack)
{
	t_stack	*current;
	t_stack	*last;

	current = stack;
	last = NULL;
	while (current->next != NULL)
	{
		last = current;
		current = current->next;
	}
	if (last != NULL)
		last->next = NULL;
	return (current);
}

void	add(t_stack *stack, void *data)
{
	t_stack	*current;
	t_stack	*next;

	current = stack;
	if (current->value == NULL)
	{
		current = (t_stack *)malloc(sizeof(t_stack));
		current->next = NULL;
		current->prev = NULL;
		current->value = data;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	next = (t_stack *)malloc(sizeof(t_stack));
	next->value = data;
	next->next = NULL;
	next->prev = current;
	current->next = next;
}

t_stack	*top(t_stack *stack)
{
	t_stack	*current;

	current = stack;
	while (current->next != NULL)
		current = current->next;
	return (current);
}
