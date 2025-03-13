NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include
RM = rm -f

SANITIZE = -fsanitize=address -g

#_____BUILTINS_____#

SRC_CD = 		builtins/cd/utils/cd_handle_home.c builtins/cd/utils/cd_is_home.c builtins/cd/cd.c
SRC_ECHO = 		builtins/echo/utils/echo_is_n.c builtins/echo/echo.c
SRC_ENV = 		builtins/env/env.c
SRC_EXIT = 		builtins/exit/utils/exit_is_valid_status.c builtins/exit/utils/ft_atol.c builtins/exit/exit.c
SRC_EXPORT =	builtins/export/utils/sort/ft_lstadd_back_env_copy.c builtins/export/utils/sort/ft_lstenv_copy.c \
				builtins/export/utils/sort/ft_lstsort_copy_env.c builtins/export/utils/sort/ft_lstswap_copy_env.c \
				builtins/export/utils/export_handle_argument.c builtins/export/utils/export_print.c \
				builtins/export/export.c
SRC_PWD = 	 	builtins/pwd/pwd.c
SRC_UNSET = 	builtins/unset/unset.c
SRC_BUILTINS =	builtins/utils/is_builtin.c builtins/utils/print_error.c builtins/builtin.c
			  
#____ENVIRONMENT_____#

SRC_ENVIRONMENT	= environment/utils/ft_is/ft_isin_env.c environment/utils/ft_is/isvalid_env_key.c \
				environment/utils/gc/ft_free_env.c environment/utils/gc/ft_gc_env.c \
				environment/utils/gc/ft_malloc_env.c \
				environment/utils/list/ft_lstadd_back_env.c environment/utils/list/ft_lstnew_env_from_str.c \
				environment/utils/list/ft_lstnew_env.c environment/utils/list/ft_lstremove_env.c \
				environment/utils/list/ft_lstsize_env.c \
				environment/utils/string/ft_copy_env.c environment/utils/string/ft_strdup_env.c \
				environment/utils/string/ft_strjoin_env.c \
				environment/utils/ft_append_env.c environment/utils/ft_update_env.c \
				environment/utils/get_env_list.c environment/utils/set_shlvl.c \
				environment/init_env.c

#_____EXECUTION______#

SRC_EXECUTION = execution/heredoc/utils/get_random_name.c  execution/heredoc/init_heredoc.c \
				execution/utils/get_command_path.c \
				execution/execution.c  execution/redirect_io.c

#_______HELPER______#

SRC_HELPER =	helper/get_number_of_arguments.c helper/get_number_of.c \
				helper/get_str.c helper/get_token_type.c helper/is_type.c
				
#_______LIBFT_______#

SRC_LIBFT =		libft/ft_function/ft_error.c libft/ft_function/ft_close.c libft/ft_function/ft_dup.c \
				libft/ft_function/ft_dup2.c libft/ft_function/ft_exit.c libft/ft_function/ft_fork.c \
				libft/ft_function/ft_pipe.c libft/ft_function/ft_chdir.c libft/ft_function/ft_getenv.c \
				libft/ft_function/ft_open.c libft/ft_function/ft_readline.c \
				libft/ft_is/ft_isallspace.c libft/ft_is/ft_isalnum.c libft/ft_is/ft_isalpha.c \
				libft/ft_is/ft_isdigit.c libft/ft_is/ft_isin.c libft/ft_is/ft_isspace.c \
				libft/gc/ft_free.c libft/gc/ft_gc.c libft/gc/ft_malloc.c \
				libft/num/ft_atoi.c libft/num/ft_itoa.c \
				libft/print/ft_putchar_fd.c libft/print/ft_putendl_fd.c libft/print/ft_putstr_fd.c \
				libft/string/ft_copy.c libft/string/ft_split.c libft/string/ft_strcmp.c libft/string/ft_strcspn.c \
				libft/string/ft_strdup.c libft/string/ft_strjoin.c libft/string/ft_strlen.c libft/string/ft_strncmp.c \
				libft/string/ft_strspn.c libft/string/ft_trim.c \
				

#_______PARSING______#

SRC_PARSING =	parsing/expander/utils/ft_isvalid_expand.c parsing/expander/expand_str.c parsing/expander/expand_token.c \
				parsing/lexer/utils/list/ft_lstadd_back_token.c parsing/lexer/utils/list/ft_lstnew_token.c \
				parsing/lexer/utils/join_tokens.c parsing/lexer/utils/get_next_token_len.c \
				parsing/lexer/utils/tokenize.c parsing/lexer/lexer.c \
				parsing/parser/utils/handle_redirection.c parsing/parser/utils/parse_token.c parsing/parser/parser.c \
				parsing/syntax/is_valid_operator.c parsing/syntax/is_valid_quotes.c \


SRC = $(SRC_CD) $(SRC_ECHO) $(SRC_ENV) $(SRC_EXIT) \
	  $(SRC_EXPORT) $(SRC_PWD) $(SRC_UNSET) $(SRC_BUILTINS) \
	  $(SRC_ENVIRONMENT) $(SRC_EXECUTION) $(SRC_HELPER) $(SRC_LIBFT) \
	  $(SRC_PARSING) main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -lreadline -o $@ $(SANITIZE)

%.o : %.c include/minishell.h
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(SANITIZE)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: clean