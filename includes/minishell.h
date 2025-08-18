/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/18 14:01:29 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

/*
	minishell.h
	Extern global to manipulate exit status from the last command
*/

typedef enum	exit_codes
{
	T_SUCCESS = 0,
	T_GENERAL_ERROR = 1,
	T_NON_EXISTENT_FILE = 1,
	T_FILE_PERMITS = 1,
	T_SYNTAX = 2,
	T_NON_EXISTENT_DIRECTORY = 2,
	T_DIRECTORY_PERMITS = 2,
	T_EXECUTABLE_PERMITS = 126,
	T_COMMAND_NOT_FOUND = 127,
	T_SIGINT = 130,
}			t_exit_types;

typedef struct	s_global
{
	int exit_status;
}				t_global;

extern t_global	g_status;


/*
	tokenizer.h
	Enum to diff the different types in the token_list and struct
	to five the token list in linked list to parser.
*/
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
}			t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;

/*
	parser.h
	Enum to separate the differents commands and know if its necesarry 
	pipes or only do, have better the connector in the same struct.
	If the value of the connector its NULL, its only 1 command, or the last. 
	Struct to give to the expansor/ executor to exapnsion.
	execute more easy.
*/
typedef enum e_connector_type
{
	PIPE_CONNECTOR = 1,
	AND_CONNECTOR = 2,
	OR_CONNECTOR = 3,

}			t_connector_type;

typedef struct s_redirect
{
	char	*infile;
	char	*outfile;
	bool	append;
	bool	heredoc;
	char	*delimiter;
}			t_redirect;

typedef struct s_command
{
	char		**command;
	t_redirect	*redirection;
	t_connector_type	connector;
	struct s_command	*next;
}			t_command;


// banner.c
void		ft_print_banner(void);

// signals.c
void		ft_set_signal_prompt_mode(void);

//global.c
void		ft_set_global_exit_status(int new_exit_code);

//minishell.c
void		ft_input_loop(char **envp);//to print all time minshell and get the input

// tokenizer_utils.c
int			ft_is_quote(char c);
int			ft_is_operator(char c);
// token.c
t_token		*ft_init_token(char *content);
// tokenizer.c
t_token		*ft_tokenizer(char *input);

// syntax_checker_utils.c
int			ft_check_content_quotes(char *input);
// sytax_checker
int			ft_check_start_end_types(t_token *token);
int			ft_check_quotes(t_token *token);
int			ft_check_parenthesis(t_token *token);
int			ft_check_redirects(t_token *token);
int			ft_check_between_operator(t_token *token);
int			ft_check_open_parenthesis(t_token *token);
int			ft_check_close_parenthesis(t_token *token);
int			ft_check_if_have_parenthesis(t_token *token);
// syntax.c
bool		ft_syntax(t_token *token);

//init_parser_struct.c
t_redirect	*ft_create_redirection_struct(void);
t_command	*ft_create_command_struct(void);
char		**ft_alloc_argv_according_correct_t_words(t_token *start, t_token *end);
//parser_redirection_utils
int	ft_have_any_redirection(t_token *start, t_token *end);
// parser_utils.c
int		ft_count_command(t_token *token_list);
int		ft_check_if_end_command(t_token *token);
t_token	*ft_get_previos_token(bool is_first, t_token *start, t_token *to_find);
int		ft_get_if_its_redirection_type(t_token * t);
void	ft_add_command_to_linked_list(t_command *new_command, t_command *top);
//parser.c
t_command	*ft_tokens_to_command_struct(t_token *token_list);

// exit.c
void		ft_exit_free_prompt(char *input);

//free.c
void    ft_free_token_and_input(char *input, t_token *token_list);


//testinf
void		ft_print_tokens(t_token	*token);
void		ft_print_command_list(t_command	*command_list);

#endif
