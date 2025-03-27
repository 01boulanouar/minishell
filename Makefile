NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include
RM = rm -f

SANITIZE = -fsanitize=address -g


SRC_BUILTINS = 	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c \
				builtins/export_sort.c builtins/export.c builtins/pwd.c builtins/unset.c \
				builtins/builtin.c
			  

SRC_ENVIRONMENT	= environment/ft_gc_env.c environment/ft_lst_env.c \
				environment/ft_string_env.c environment/ft_update_env.c environment/init_env.c 

SRC_EXECUTION = execution/execution.c  execution/exit_status.c \
				execution/get_command_path.c execution/heredoc.c \
				execution/print_error.c execution/redirect_io.c execution/signal.c


SRC_HELPER = helper/get_number_of.c helper/is_type.c
				

SRC_LIBFT =		libft/ft_function/ft_close.c libft/ft_function/ft_execve.c \
				libft/ft_function/ft_dup2.c libft/ft_function/ft_exit.c libft/ft_function/ft_fork.c \
				libft/ft_function/ft_pipe.c libft/ft_function/ft_chdir.c libft/ft_function/ft_getenv.c \
				libft/ft_function/ft_open.c libft/ft_function/ft_readline.c libft/ft_function/ft_wait.c \
				libft/ft_is/ft_isallspace.c libft/ft_is/ft_isalnum.c libft/ft_is/ft_isalpha.c \
				libft/ft_is/ft_isdigit.c libft/ft_is/ft_isin.c libft/ft_is/ft_isspace.c \
				libft/gc/fd_gc.c libft/gc/ft_free.c libft/gc/ft_gc.c libft/gc/ft_malloc.c \
				libft/num/ft_atoi.c libft/num/ft_itoa.c \
				libft/print/ft_putchar_fd.c libft/print/ft_putendl_fd.c libft/print/ft_putstr_fd.c \
				libft/string/ft_copy.c libft/string/ft_split.c libft/string/ft_strcmp.c libft/string/ft_strcspn.c \
				libft/string/ft_strdup.c libft/string/ft_strjoin.c libft/string/ft_strlen.c libft/string/ft_strncmp.c \
				libft/string/ft_strspn.c libft/string/ft_trim.c

SRC_PARSING =	parsing/expander.c parsing/lexer.c parsing/parser.c \
				parsing/syntax_error.c parsing/utils/ft_lst_token.c \
				parsing/utils/get_next_token_len.c parsing/utils/get_token_type.c

SRC = $(SRC_BUILTINS) $(SRC_ENVIRONMENT) $(SRC_EXECUTION) \
	$(SRC_HELPER) $(SRC_LIBFT) $(SRC_PARSING) \
	main.c

OBJ = $(SRC:.c=.o)

# READLINE_INC = -I$(shell brew --prefix readline)/include
# READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@ $(READLINE_LIB) $(SANITIZE)

%.o : %.c include/minishell.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(READLINE_INC) $(SANITIZE)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: clean
