#ifndef PIPES_H
 #define PIPES_H

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

#endif
