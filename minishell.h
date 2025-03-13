/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 14:50:48 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/*---------------HEREDOC----------------*/

# define HEREDOC_NAME "/tmp/.heredoc_"

/*----------------TOKENS----------------*/

# define PIPE '|'
# define LESS '<'
# define GREATER '>'
# define DOLLAR '$'
# define EQUAL '='
# define PLUS '+'
# define UNDERSCORE '_'

# define DOUBLE_GREATER ">>"
# define DOUBLE_LESS "<<"
# define EXIT_STATUS "$?"
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

# define BLANKS " 	"
# define SEPARATORS " 	\'\"<>|$"

/*----------------EXIT CODES--------------*/

# define EXIT_SYNTAX_ERROR 258

/*---------------ERROR STRINGS------------*/

# define SYNTAX_ERROR_STR "syntax error near unexpected token"
# define GETCWD_ERROR_STR "error retrieving current directory: \
							getcwd: cannot access parent directories: \
							No such file or directory"

/*------------------ENUMS-----------------*/

typedef enum e_token_type
{
	t_word,
	t_pipe,
	t_less,
	t_greater,
	t_double_less,
	t_double_greater,
	t_single_quote,
	t_double_quote,
	t_single_dollar,
	t_dollar_num,
	t_dollar_expand,
	t_exit_status,
	t_expanded,
}					t_token_type;

/*------------------STRUCTS-----------------*/

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				before_space;
	struct s_token	*next;
}					t_token;

typedef struct s_redirect
{
	t_token			file;
	t_token_type	type;
}					t_redirect;

typedef struct s_command
{
	t_token			**tokens;
	t_redirect		**out_files;
	t_redirect		**in_files;
	int				not_to_be_executed;
	int				heredoc_pos;
}					t_command;

typedef struct s_env
{
	char			*key;
	char			*operator;
	char			*value;
	struct s_env	*next;

}					t_env;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;

}					t_gc;

/*------------------FUNCTIONS-----------------*/

/*---------builtins----------*/

// builtins.c
int					is_builtin(t_command command);
int					exec_builtin(t_command command);

// cd.c
int					cd_builtin(t_command command);

// echo.c
int					echo_builtin(t_command command);

// env.c
int					env_builtin(t_command command);

// exit.c
int					exit_builtin(t_command command);

// export_sort.c
t_env				*sort_env(void);

// export.c
void				ft_update_env(char *key, char *value, int append);
int					export_builtin(t_command command);

// pwd.c
int					pwd_builtin(void);

// unset.c
int					unset_builtin(t_command command);

/*---------env----------*/

// ft_getenv.c
t_env				**get_env_list(void);
int					is_valid_env_key(char *key);
char				*ft_getenv(char *name);

// gc.c
void				*ft_malloc_env(size_t size);
void				ft_free_env(void);

// init.c
void				init_env(char **line);

// utils.c
char				*ft_copy_env(const char *start, const char *end);
char				*ft_strdup_env(const char *s1);
char				*ft_strjoin_env(char const *s1, char const *s2);

/*---------execution----------*/

// execution_helper.c
void				ft_close(int fd);
void				dup_2(int old, int new);
char				*get_random_name(void);

// execution.c
void				exec(t_command *commands, int n_commands, char **heredoc,
						int n_herdocs);

// heredoc.c
char				**init_herdoc(t_token *token);

// redirect_io.c
void				cleanup_heredocs(char **heredoc, int num_herdocs);
char				*heredoc_1(t_redirect *redirect, char **heredoc,
						int heredoc_index);
void				redirect_io(t_command cmd, char **heredoc, int heredoc_pos);

/*---------helper----------*/

// get_next_token_len.c
size_t				get_next_token_len(const char *line);

// get_number_of_arguments.c
int					get_number_of_arguments(t_command command);

// get_number_of.c
int					get_number_of_tokens(t_token *token);
int					get_number_of_commands(t_token *token);
int					get_number_of_infiles(t_token *token);
int					get_number_of_outfiles(t_token *token);
int					get_number_of_herdocs(t_token *token);

// get_str.c
char				**get_command_str(t_command command);
char				**get_env_str(void);

// get_token_type.c
t_token_type		get_token_type(const char *value);

// is_type.c
int					is_redirection(t_token *token);
int					is_pipe(t_token *token);
int					is_operator(t_token *token);

/*---------parsing----------*/

// expander.c
void				expand(t_token **token, char *line, char *value);
char				*expand_double_quotes(char *line);

// lexer.c
t_token				*lexer(void);

// parser.c
t_command			*parser(t_token *token);

// syntax_error.c
int					is_valid_quotes(const char *line);
int					operator_error(t_token *token);

/*---------utils----------*/

// ft_atoi.c
int					ft_atoi(const char *nbr);

// ft_copy.c
size_t				ft_strlen(const char *s);
char				*ft_copy(const char *start, const char *end);
char				*ft_trim(char *line);
char				*ft_strdup(const char *s1);

// ft_isdigit.c
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isvalid(int c);

// ft_itoa.c
char				*ft_itoa(int n);

// ft_split.c
char				**ft_split(char const *s, char c);

// ft_strjoin.c
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_space(char const *s1, char const *s2);

// lst_env.c
t_env				*ft_lstnew_env(char *key, char *operator, char *value);
t_env				*ft_lstnew_env_from_str(char *str);
void				ft_lstadd_back_env(t_env *new);
void				ft_lstremove_env(char *key);
int					ft_lstsize(t_env *env);

// lst_token.c
t_token				*ft_lstnew_token(char *value, t_token_type type,
						int before_space);
void				ft_lstadd_back_token(t_token **lst, t_token *new);

// print.c
int					ft_isspace(char c);
int					ft_isallspace(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

// string.c
int					ft_isin(const char c, const char *charset);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*---------minishell----------*/

// error_messages.c
void				print_error(int print_name, char *function, char *file,
						char *error);

// garbage_collector.c
void				*ft_malloc(size_t size);
void				ft_free_command(void);

// main.c

#endif
