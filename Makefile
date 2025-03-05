CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g
NAME = minishell
RM = rm -f


SRC_HELPER = helper/get_number_of.c helper/is.c helper/get_token_type.c helper/get_next_token_len.c
SRC_UTILS = utils/ft_copy.c utils/lst_token.c  utils/lst_env.c utils/ft_split.c utils/ft_isdigit.c  utils/print.c utils/string.c  utils/ft_atoi.c
SRC_BUILTINS = builtins/cd.c builtins/echo.c builtins/env.c \
			   builtins/exit.c builtins/export.c builtins/export_sort.c builtins/pwd.c builtins/unset.c  builtins/builtin.c

SRC = main.c lexer.c environment.c parser.c expander.c syntax_error.c garbage_collector.c exec.c \
		$(SRC_BUILTINS) $(SRC_HELPER) $(SRC_UTILS) to_delete.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -lreadline -o $@ $(SANITIZE)
	@$(RM) $(OBJ) # to remove

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@ $(SANITIZE)


clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: clean