NAME := minishell

CC := cc
CFLAGS := -Wextra -Wall -Werror -g -fsanitize=address -O1
LDFLAGS := -lreadline -lft

SRCDIR := src/

SOURCES := $(SRCDIR)main.c \
		   $(SRCDIR)buildins/change_dir.c \
		   $(SRCDIR)buildins/get_dir.c \
		   $(SRCDIR)buildins/env.c \
		   $(SRCDIR)prompt/prompt.c \
		   $(SRCDIR)input_parsing/tokenize.c \
		   $(SRCDIR)input_parsing/stack_utils.c \
		   $(SRCDIR)input_parsing/input_validator.c \
		   $(SRCDIR)input_parsing/expander.c \
		   $(SRCDIR)input_parsing/token_utils.c \
		   $(SRCDIR)signals/ctrl.c

OBJECTS := $(SOURCES:.c=.o)

LIBFT := lib/libft

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME) -L $(LIBFT) 

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJECTS)
	
fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

test:
	valgrind --leak-check=full ./$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
