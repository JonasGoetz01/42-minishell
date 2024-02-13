NAME = minishell

INCLUDES = -I lib/libft -I inc

CC = cc

SRCDIR = src/
SRCS = $(SRCDIR)main.c
OBJS	:= ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

LIBS = lib/libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

libft:
	make -C lib/libft

clean:
	make clean -C lib/libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C lib/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
