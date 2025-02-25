/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 15:17:00 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define SYNTAX_ERROR_STR "minishell: syntax error near unexpected token\n"

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

// Token struct
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				after_space;
	int				expanded;
	struct s_token	*next;
}					t_token;

// comand struct
typedef struct s_redirect
{
	char			*file;
	char			*type;
}					t_redirect;

typedef struct s_comand
{
	t_token			**tokens;
	t_redirect		**out_files;
	t_redirect		**in_files;
	int				not_to_be_executed;
}					t_comand;

typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;

}					t_node;

size_t				ft_strlen(const char *s);
int					ft_isin(const char c, const char *charset);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_copy(const char *start, const char *end);
char				*ft_trim(char *line);

void				ft_putstr_fd(const char *s, int fd);
int					ft_isdigit(int c);

t_token				*ft_lstnew(char *value, t_token_type type, int after_space,
						int expanded);
void				ft_lstadd_back(t_token **lst, t_token *new);
void				ft_lstfree(t_token **lst);

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

void				handle_redirection(t_comand *cmd, t_token *token,
						int *in_index, int *out_index);
t_comand			*parser(t_token *token);

int					operator_error(t_token *token);

void				*ft_malloc(size_t size);
void				ft_free(void);

char				*print_token_type(t_token_type type);
void				print_tokens(t_token *token);
void				print_commands(t_comand *commands, int num_commands);
#endif