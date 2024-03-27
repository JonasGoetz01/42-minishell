#ifndef BUILDINS_H
 #define BUILDINS_H

 #include <sys/types.h>

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_process
{
	int		pipe_fd_in[2];
	int		pipe_fd_out[2];
	char	*cmd;
	char	**args;
	pid_t	pid;
}			t_process;

typedef struct s_command
{
	char		*limiter;
	int			fd_in;
	int			fd_out;
	int			process_len;
	int			start_arg;
	t_process	**processes;
}				t_cmd;

#endif
