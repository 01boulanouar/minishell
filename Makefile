NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c lexer.c lexer_utils.c utils/string.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@
	$(RM) $(OBJ)

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean