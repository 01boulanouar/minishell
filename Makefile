CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g
NAME = minishell
RM = rm -f


SRC_HELPER = helper/get_number_of.c helper/is.c helper/get.c
SRC_UTILS = utils/copy.c utils/list.c utils/print.c utils/string.c

SRC = main.c lexer.c parser.c expander.c syntax_error.c garbage_collector.c \
		$(SRC_HELPER) $(SRC_UTILS) to_delete.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@ $(SANITIZE)
	@$(RM) $(OBJ) # to remove

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SANITIZE)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: clean