/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/14 14:06:40 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

int					g_in_shell;

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
# define D_BLANKS " 	$"
# define SEPARATORS " 	\'\"<>|$"
# define D_SEP " 	\'\"<>|"

/*----------------ft_exit CODES--------------*/

# define EXIT_SYNTAX_ERROR 258
# define EXIT_BUILTIN_BAD_USAGE 2
# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126

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

/*---------lexer----------*/

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				after_space;
	struct s_token	*next;
}					t_token;

/*---------parser----------*/

typedef struct s_redirect
{
	t_token			file;
	t_token_type	type;
}					t_redirect;

typedef struct s_command
{
	t_token			**tokens;
	t_redirect		**files;
	int				not_to_be_executed;
	int				heredoc_pos;
	int				is_last;
}					t_command;

/*---------environment----------*/

typedef struct s_env
{
	char			*key;
	char			*operator;
	char			*value;
	struct s_env	*next;

}					t_env;

/*---------garbage collector----------*/

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;

}					t_gc;

/*------------------FUNCTIONS-----------------*/

/*---------builtins----------*/

// cd.c
int					cd_builtin(t_command command);

// echo.c
int					echo_builtin(t_command command);

// env.c
int					env_builtin(t_command command);

// ft_exit.c
int					exit_builtin(t_command command, int should_exit);

// export.c
void				ft_lstadd_back_env_copy(t_env **lst, t_env *new);
t_env				*ft_lstenv_copy(void);
t_env				*ft_lstsort_copy_env(void);
void				ft_lstswap_copy_env(t_env *node, t_env *next);
void				export_handle_argument(t_env *node);
int					export_print(void);
int					export_builtin(t_command command);

// pwd.c
int					pwd_builtin(void);

// unset.c
int					unset_builtin(t_command command);

// builtins.c
int					is_builtin(t_command command);
void				print_error(int print_name, char *function, char *file,
						char *error);
int					exec_builtin(t_command command);

/*---------env----------*/

int					ft_isin_env(char *key);
int					ft_isvalid_env_key(char *key);

void				ft_free_env(void);
t_gc				**ft_gc_env(void);

void				ft_lstadd_back_env(t_env *new);
t_env				*ft_lstnew_env_from_str(char *str);
t_env				*ft_lstnew_env(char *key, char *operator, char *value);
void				ft_lstremove_env(char *key);
int					ft_lstsize_env(t_env *env);
int					ft_isvalid_expand(int c);
char				*ft_copy_env(const char *start, const char *end);
char				*ft_strdup_env(const char *s1);
char				*ft_strjoin_env(char const *s1, char const *s2);

void				ft_update_env(char *key, char *value);
void				ft_append_env(char *key, char *value);
t_env				**get_env_list(void);
void				set_shlvl(t_env *node);
void				init_env(char **line);

/*---------execution----------*/

// execution.c
char				*get_command_path(char *executable);
char				**get_command_str(t_command command);
char				**get_env_str(void);

char				*get_random_name(void);
char				**init_heredoc(t_token *token);

int					exec(t_command *commands, int n_commands, char **heredoc,
						int n_heredocs);

// redirect_io.c
void				cleanup_heredocs(char **heredoc, int num_heredocs);
char				*read_from_heredoc(t_redirect *redirect, char **heredoc,
						int heredoc_index);
void				redirect_io(t_command *cmd, char **heredoc,
						int heredoc_pos);

void				sigint_handler(int signal);
/*---------helper----------*/

// get_number_of_arguments.c
int					get_number_of_arguments(t_command command);

// get_number_of.c
int					get_number_of_tokens(t_token *token);
int					get_number_of_commands(t_token *token);
int					get_number_of_files(t_token *token);
int					get_number_of_heredocs(t_token *token);

// get_token_type.c
t_token_type		get_token_type(const char *value);

// is_type.c
int					is_redirection(t_token *token);
int					is_pipe(t_token *token);
int					is_quotes(t_token *token);
int					is_operator(t_token *token);
int					is_dollar_str(char *str);

/*---------libft----------*/

int					ft_close(int fd);
void				ft_execve(t_command command);
int					ft_dup2(int oldfd, int newfd);
void				ft_exit(int status);
char				*ft_getcwd(void);
int					ft_pipe(int fildes[2]);
int					ft_chdir(char *path);
char				*ft_getenv(char *name);
int					ft_open(const char *path, int oflag);
int					ft_open_create(const char *path, int oflag, int mode);
char				*ft_real_path(char *path);
char				*ft_readline(const char *prompt);

int					ft_isallspace(char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isin(const char c, const char *charset);
int					ft_isspace(char c);

void				*ft_malloc_env(size_t size);
void				ft_free(void);
t_gc				**ft_gc(void);
void				*ft_malloc(size_t size);

int					ft_atoi(const char *nbr);
char				*ft_itoa(int n);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

char				*ft_copy(const char *start, const char *end);
char				**ft_split(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strcspn(const char *s, const char *reject);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_space(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strspn(const char *s, const char *accept);
char				*ft_trim(char *line);
void				ft_wait(pid_t *last_pid);

/*---------parsing----------*/

// expander.c
int					ft_isvalid_expand(int c);
int					expand_token(t_token **token, char *name, int a_s);
char				*expand_str(char *line);

// lexer.c
void				ft_lstadd_back_token(t_token **lst, t_token *new);
t_token				*ft_lstnew_token(char *value, t_token_type type,
						int after_space);
t_token				*ft_last_token(t_token **lst);
size_t				get_next_token_len(const char *line);
void				join_token(t_token **token);
t_token				*tokenize(char *line);
t_token				*lexer(void);

// parser.c
void				handle_redirection(t_command *cmd, t_token *token,
						int *index);
t_token				*parse_token(t_command *command, t_token *token,
						int *count);
t_command			*parser(t_token *token);

// syntax.c
int					is_valid_quotes(const char *line);
int					is_valid_operator(t_token *token);

void				close_all_fds(void);

int					*ft_get_exit_status(void);
void				ft_set_exit_status(int new_status);

void				save_terminal_settings(void);
void				restore_terminal_settings(void);

#endif
