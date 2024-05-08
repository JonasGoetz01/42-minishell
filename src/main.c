#include "../inc/minishell.h"

void	print_welcome_message(t_global *global)
{
	char	*pgrossma;
	char	*jgotz;
	char	*username;

	pgrossma = "https://profile.intra.42.fr/users/pgrossma";
	jgotz = "https://profile.intra.42.fr/users/jgotz";
	printf("\x1b[2J%s", PAS1);
	printf("%s\t██████  ██████  ███████ ██   ██\n", PAS2);
	printf("%s\t██   ██ ██   ██ ██      ██   ██\n", PAS3);
	printf("%s\t██   ██ ██████  ███████ ███████\n", PAS4);
	printf("%s\t██   ██ ██           ██ ██   ██\n", PAS5);
	printf("%s\t██████  ██      ███████ ██   ██\n", PAS6);
	printf("\x1b[0m\n\n\t\tDont panic shell\n\n");
	printf("\t\t\e]8;;%s\apgrossma\e]8;;\a && \e]8;;%s\ajgotz\e]8;;\a\n\n\n",
		pgrossma, jgotz);
	username = ft_get_env("USER", global->envv);
	if (username)
	{
		printf("\n✨ Hello, %s ✨\n", username);
		free(username);
	}
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
	ft_increase_shlvl(&global);
	while (true)
	{
		if (show_prompt(&global) || global.should_exit)
			break ;
	}
	ft_free_global(&global);
	return (global.exit_status);
}
