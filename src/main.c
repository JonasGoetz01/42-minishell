/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/14 19:00:36 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE 100

int	main(void)
{
	signal(SIGINT, handle_sigint);
	while (1)
	{
		if (show_prompt())
			break ;
	}
	return (0);
}
