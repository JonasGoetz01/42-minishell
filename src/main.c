/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 15:20:30 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE 100

int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		if (show_prompt(envv))
			break ;
	}
	return (0);
}
