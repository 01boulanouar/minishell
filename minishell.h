/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/03 18:05:37 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/stat.h>

// Tokens
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
# define DOUBLE_QUOTE '\"'

// Separators
# define BLANKS " 	"
# define SEPARATORS " 	\'\"<>|$"

// Error Codes
# define EXIT_SYNTAX_ERROR 258

// Error String
# define SYNTAX_ERROR_STR "minishell: syntax error near unexpected token"

// Token types
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
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				before_space;
	int				expanded;
	struct s_token	*next;
}					t_token;

typedef struct s_redirect
{
	char			*file;
	t_token_type	type;
}					t_redirect;

typedef struct s_command
{
	t_token			**tokens;
	t_redirect		**out_files;
	t_redirect		**in_files;
	int				not_to_be_executed;
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

size_t				ft_strlen(const char *s);
int					ft_isin(const char c, const char *charset);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_copy(const char *start, const char *end);
char				*ft_trim(char *line);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2, int space);
int 				ft_isspace(char c);
int					ft_isallspace(char *str);
int					ft_atoi(const char *nbr);
char				*ft_itoa(int n);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isvalid(int c);


void				ft_update_env(char *key, char *value, int append);
t_token				*ft_lstnew_token(char *value, t_token_type type,
						int before_space, int expanded);
t_env				*ft_lstnew_env(char *key, char *operator, char * value);
t_env				*ft_lstnew_env_from_str(char *str);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
void				ft_lstadd_back_env(t_env *new);
void				ft_lstremove_env(char *key);
void				ft_lstfree_copy_env(t_env **env);

char				*ft_strdup_env(const char *s1);
void				init_env(char **line);
t_env				**get_env_head(void);
char				*ft_getenv(char *name);
t_env				*sort_env(void);

int					is_redirection(t_token *token);
int					is_operator(t_token *token);
int					is_valid_env_key(char *key);

int					get_number_of_tokens(t_token *token);
int					get_number_of_infiles(t_token *token);
int					get_number_of_outfiles(t_token *token);
int					get_number_of_commands(t_token *token);
int					get_number_of_arguments(t_command command);

t_token_type		get_token_type(const char *value);
size_t				get_next_token_len(const char *line);

int					is_valid_quotes(const char *line);
t_token				*lexer(void);
size_t				get_next_token_len(const char *line);
void				expand_token(t_token **token, char *name, int before_space);
char				*expand_double_quotes(char *line);

void				handle_redirection(t_command *cmd, t_token *token,
						int *in_index, int *out_index);
t_command			*parser(t_token *token);

int					operator_error(t_token *token);

void				*ft_malloc(size_t size);
void				ft_free(void);

int					cd_builtin(t_command command);
int					echo_builtin(t_command command);
int					pwd_builtin(void);
int					env_builtin(t_command command);
int					export_builtin(t_command command);
int					exit_builtin(t_command command);
int					unset_builtin(t_command command);
int					is_builtin(t_command command);
int					exec_builtin(t_command command);

void				exec(t_command *commands);

char				*print_token_type(t_token_type type);
void				print_tokens(t_token *token);
void				print_commands(t_command *commands, int num_commands);
#endif