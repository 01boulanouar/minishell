/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 16:25:45 by moboulan         ###   ########.fr       */
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
# define SQUOTE '\''
# define DQUOTE '\"'
# define PIPE '|'
# define LESS '<'
# define GREATER '>'
# define DGREATER ">>"
# define DLESS "<<"
# define DOLLAR '$'

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
	t_pipe,
	t_less,
	t_greater,
	t_dless,
	t_dgreater,
	t_word,
	t_squote,
	t_dquote,
	t_dollar,
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

}					t_comand;

typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;

}					t_node;

// String Utils
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(const char *s, int fd);
int					ft_isin(const char c, const char *charset);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
char				*ft_copy(const char *start, const char *end);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_skip_blanks(const char *line);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// List Utils
t_token				*ft_lstnew(char *value, t_token_type type, int after_space,
						int expanded);
void				ft_lstadd_back(t_token **lst, t_token *new);
void				ft_lstfree(t_token **lst);

// Lexer Functions
char				*lex_print_token_type(t_token_type type);
t_token_type		lex_token_type(const char *value);
int					lex_is_valid_syntax(const char *line);
char				*lex_trim(char *line);
t_token				*lexer(char *line);
int					lex_is_valid_pipes(const char *line);
size_t				lex_get_next_token(const char *line);
int					lex_expand(t_token **token, char *name);

// parser functions
int					parse_is_redirection(t_token *token);
int					parse_number_of_commands(t_token *token);
int					parse_out_files_number(t_token *token);
int					parse_in_files_number(t_token *token);
int					parse_n_tokens(t_token *token);
void				parse_handle_redirection(t_comand *cmd, t_token *token,
						int *in_index, int *out_index);
t_comand			*parser(t_token *token);

// syntax error
int					operator_error(t_token *token);

// garbage collector
void				*ft_malloc(size_t size);
void				ft_free(void);

#endif