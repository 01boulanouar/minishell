/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:37:46 by moboulan         ###   ########.fr       */
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

// Tokens
# define PIPE '|'
# define LESS '<'
# define GREATER '>'
# define DOLLAR '$'
# define EQUAL '='

# define DOUBLE_GREATER ">>"
# define DOUBLE_LESS "<<"

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
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				after_space;
	int				expanded;
	struct s_token	*next;
}					t_token;

typedef struct s_redirect
{
	char			*file;
	char			*type;
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
char				*ft_strjoin(char const *s1, char const *s2);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_isdigit(int c);

t_token				*ft_lstnew_token(char *value, t_token_type type,
						int after_space, int expanded);
t_env				*ft_lstnew_env(char *key, char *value);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
void				ft_lstadd_back_env(t_env **lst, t_env *new);

t_env				*handle_env(char **line);

int					is_redirection(t_token *token);
int					is_operator(t_token *token);

int					get_number_of_tokens(t_token *token);
int					get_number_of_infiles(t_token *token);
int					get_number_of_outfiles(t_token *token);
int					get_number_of_commands(t_token *token);

t_token_type		get_token_type(const char *value);

int					is_valid_quotes(const char *line);
t_token				*lexer(char *line);
size_t				get_next_token_len(const char *line);
void				expand_token(t_token **token, char *name, int after_space);
char				*expand_double_quotes(char *line);

void				handle_redirection(t_command *cmd, t_token *token,
						int *in_index, int *out_index);
t_command			*parser(t_token *token);

int					operator_error(t_token *token);

void				*ft_malloc(size_t size);
void				ft_free(void);

int					pwd_builtin(void);
int					env_builtin(t_env *env);
int					is_builtin(t_command command);
int					exec_builtin(t_command command, t_env *env);

void				exec(t_command *commands, t_token *tokens, t_env *env);

char				*print_token_type(t_token_type type);
void				print_tokens(t_token *token);
void				print_commands(t_command *commands, int num_commands);
#endif