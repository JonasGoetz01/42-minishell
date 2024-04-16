NAME	:=	minishell

CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror #-g -fsanitize=address -O1
LDFLAGS	:=	-lreadline -lft
LIBFT	:=	lib/libft

VPATH	:=	src \
			src/buildins \
			src/prompt \
			src/input_parsing \
			src/signals \
			src/utils \
			src/exec \
			inc

INC		:=	colors.h \
			exec.h \
			minishell.h

SOURCES	:=	main.c \
			cd_buildin.c \
			error_buildins.c \
			exec_buildins.c \
			pwd_buildin.c \
			env_buildin.c \
			echo_buildin.c \
			exit_buildin.c \
			unset_buildin.c \
			export_buildin.c \
			get_hostname.c \
			exec_command.c \
			prompt.c \
			tokenize.c \
			stack_utils.c \
			input_validator.c \
			expander.c \
			token_utils.c \
			ctrl.c \
			fd_utils.c \
			exec_process.c \
			org_tokens.c \
			exec_tokens.c \
			exec_files.c \
			parse_process.c \
			alloc_utils.c \
			init_utils.c \
			env_utils.c \
			error_msg.c

OBJDIR	:=	obj
OBJECTS	:=	$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS) $(INC)
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

$(OBJDIR)/%.o: %.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
