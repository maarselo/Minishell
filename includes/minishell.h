/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 15:35:25 by fbanzo-s         ###   ########.fr       */
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
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;

typedef enum e_connector_type
{
	PIPE_CONNECTOR = 1,
	AND_CONNECTOR = 2,
	OR_CONNECTOR = 3,

}	t_connector_type;

typedef struct s_redirect
{
	char	*infile;
	char	*outfile;
	bool	append;
	bool	heredoc;
	char	*delimiter;
}	t_redirect;

typedef struct s_command
{
	char				**command;
	t_redirect			*redirection;
	t_connector_type	connector;
	struct s_command	*next;
}	t_command;

// banner.c
void		ft_print_banner(void);
// signals.c
void		ft_set_signal_prompt_mode(void);
// minishell.c
void		ft_input_loop(char **envp);
// token.c
t_token		*ft_init_token(char *content);
void		ft_free_token(t_token *token);
// tokenizer_utils.c
int			ft_is_quote(char c);
int			ft_is_operator(char c);
char		*ft_extract_token(char *input, int *i);
// tokenizer.c
void		ft_print_tokens(t_token	*token);
t_token		*ft_tokenizer(char *input);
// expander.c
void		ft_expand(t_command *cmd, int status);
char		*ft_expand_var(char *str, int *i, int exit_status);
// expander_utils.c
char		*ft_join_char_var(char *str, char c);
char		*ft_join_str_var(char *str, char *to_append);
char		*ft_expand_tilde(char *result);
char		*ft_handle_expansion(char *result, char *str, int *i, int exit_status);
// exit.c
void		ft_exit_free_prompt(char *input);

#endif
