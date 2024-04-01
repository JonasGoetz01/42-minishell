/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/04/01 13:41:28 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE 100

void	print_welcome_message(void)
{
	char	*pgrossma;
	char	*jgotz;

	pgrossma = "https://profile.intra.42.fr/users/pgrossma";
	jgotz = "https://profile.intra.42.fr/users/jgotz";
	char *pastel_colors[] = {
		"\x1b[38;2;255;204;204m",
		"\x1b[38;2;255;229;204m",
		"\x1b[38;2;255;242;204m",
		"\x1b[38;2;204;255;204m",
		"\x1b[38;2;204;255;255m",
		"\x1b[38;2;204;204;255m",
		"\x1b[38;2;255;204;255m",
	};
	printf("\x1b[2J%s", pastel_colors[0]);
	printf("%s\t██████  ██████  ███████ ██   ██\n", pastel_colors[1]);
	printf("%s\t██   ██ ██   ██ ██      ██   ██\n", pastel_colors[2]);
	printf("%s\t██   ██ ██████  ███████ ███████\n", pastel_colors[3]);
	printf("%s\t██   ██ ██           ██ ██   ██\n", pastel_colors[4]);
	printf("%s\t██████  ██      ███████ ██   ██\n", pastel_colors[5]);
	printf("\x1b[0m\n\n\t\tDont panic shell\n\n");
	printf("\t\t\e]8;;%s\apgrossma\e]8;;\a && \e]8;;%s\ajgotz\e]8;;\a\n\n\n",
		pgrossma, jgotz);
	printf("\n✨ Hello, %s ✨\n", get_env("USER"));
	fflush(stdout);
}

int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	(void)envv;
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);
	// print_welcome_message();
	// while (1)
	// {
	// 	if (show_prompt(envv))
	// 		break ;
	// }
	// return (0);

}
