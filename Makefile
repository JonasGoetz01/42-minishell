NAME	:=	minishell

CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g -fsanitize=address -O1
LDFLAGS	:=	-lreadline -lft
LIBFT	:=	lib/libft

VPATH	:=	src \
			src/buildins \
			src/prompt \
			src/input_parsing \
			src/signals

SOURCES	:=	main.c \
			change_dir.c \
			get_dir.c \
			env.c \
			get_hostname.c \
			exec_command.c \
			prompt.c \
			tokenize.c \
			stack_utils.c \
			input_validator.c \
			expander.c \
			token_utils.c \
			ctrl.c

OBJDIR	:=	obj
OBJECTS	:=	$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME) -L $(LIBFT)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

test:
	valgrind --leak-check=full ./$(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
