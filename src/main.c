#include "../inc/minishell.h"

t_g_signal	g_signal;

void	print_welcome_message(t_global *global)
{
	char	*pgrossma;
	char	*jgotz;
	char	*username;

	pgrossma = "https://profile.intra.42.fr/users/pgrossma";
	jgotz = "https://profile.intra.42.fr/users/jgotz";
	username = ft_get_env("USER", global->envv);
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
	if (username)
	{
		printf("\n✨ Hello, %s ✨\n", username);
		free(username);
	}
	fflush(stdout);
}

int	main(int argc, char **argv, char **envv)
{
	t_global	global;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	ft_init_t_global(&global, envv);
	if (global.isatty)
		print_welcome_message(&global);
	while (true)
	{
		if (show_prompt(&global) || global.should_exit)
			break ;
	}
	ft_free_global(&global);
	return (global.exit_status);
}
