NAME	:=	minishell

CC		:=	cc
CFLAGS	?=  -Wextra -Wall -Werror -g -fsanitize=address -O1
DEBUG ?=  1
CFLAGS += -DDEBUG=$(DEBUG)
LDFLAGS	:=	-lreadline -lft
LIBFT	:=	lib/libft

VPATH	:=	src \
			src/buildins \
			src/prompt \
			src/input_parsing \
			src/signals \
			src/utils \
			src/exec \
			inc \
			tests/unit

INC		:=	colors.h \
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
			exec_pipe.c \
			exec_heredoc.c \
			prompt.c \
			tokenize.c \
			tokenize_utils.c \
			tokenize_utils_2.c \
			input_validator.c \
			input_validator_utils.c \
			expander.c \
			token_utils.c \
			ctrl.c \
			fd_utils.c \
			exec_process.c \
			org_tokens.c \
			org_tokens_utils.c \
			exec_tokens.c \
			exec_tokens_utils.c \
			exec_process_utils.c \
			exec_utils.c \
			exec_files.c \
			parse_process.c \
			alloc_utils.c \
			init_utils.c \
			env_utils.c \
			error_msg.c \
			file_utils.c \
			ast.c \
			precedence.c \
			rearrange_tokens.c \
			rearrange_tokens_utils.c \
			next_is.c \
			retokenize.c \
			retokenize_utils.c \
			token_utils_2.c \
			cleanup.c \
			ast_utils.c \
			expand_heredoc.c \
			exec_heredoc_utils.c \
			wildcards.c \
			wildcards_tokens.c \
			wildcards_files.c

OBJDIR	:=	obj
OBJECTS	:=	$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

TESTSSRC	:=	$(TESTDIR)/test.c \
				$(TESTDIR)/helpers.c

TESTDIR := test/unit
TESTS	:=	$(addprefix $(OBJDIR), $(TESTSSRC:.c=.o))

TESTOBJECTS := $(filter-out $(OBJDIR)/main.o, $(OBJECTS))
TESTNAME := test

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
	rm -f $(TESTNAME)

re: fclean all

test:
	valgrind --leak-check=full ./$(NAME)

tester:
	cd 42_minishell_tester-master && bash tester.sh m

unit: $(TESTS) $(TESTOBJECTS) $(INC)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(TESTOBJECTS) $(TESTS) $(LDFLAGS) -o $(TESTNAME) -L $(LIBFT)
	./$(TESTNAME)

$(TESTDIR)/%.o: %.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

no-debug:
	make CFLAGS="-Wextra -Wall -Werror -DDEBUG=0" re

.PHONY: all clean fclean re
