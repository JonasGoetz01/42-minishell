/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/22 11:20:29 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE 100

void	print_welcome_message(void)
{
	char *pastel_colors[] = {
		"\x1b[38;2;255;204;204m", // pastel red
		"\x1b[38;2;255;229;204m", // pastel orange
		"\x1b[38;2;255;242;204m", // pastel yellow
		"\x1b[38;2;204;255;204m", // pastel green
		"\x1b[38;2;204;255;255m", // pastel cyan
		"\x1b[38;2;204;204;255m", // pastel blue
		"\x1b[38;2;255;204;255m", // pastel magenta
	};
	printf("\x1b[2J");
	printf("%s", pastel_colors[0]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██████  ██████  ███████ ██   ██\n",
		pastel_colors[1]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██   ██ ██      ██   ██\n",
		pastel_colors[2]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██████  ███████ ███████\n",
		pastel_colors[3]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██           ██ ██   ██\n",
		pastel_colors[4]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██████  ██      ███████ ██   ██\n",
		pastel_colors[5]);
	printf("\x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDont panic shell\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tpgrossma & jgotz\n\n\n");
	fflush(stdout);
}

int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_welcome_message();
	while (1)
	{
		if (show_prompt(envv))
			break ;
	}
	return (0);
}
