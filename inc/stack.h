/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:12:28 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 12:49:12 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

typedef struct s_stack
{
	void			*value;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

void				print_stack(t_stack *stack);
int					stack_len(t_stack *stack);
t_stack				*pop(t_stack *stack);
void				add(t_stack *stack, void *data);
t_stack				*top(t_stack *stack);

#endif
