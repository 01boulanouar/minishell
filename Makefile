NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = minishell.c split.c

OBJ = $(addprefix objects/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@

objects/%.o : mandatory/%.c mandatory/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean
