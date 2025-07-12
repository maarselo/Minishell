/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/12 23:06:14 by fbanzo-s         ###   ########.fr       */
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
}			t_token_type;

typedef struct s_cmd
{
	char	**argv;
	char	*infile;
	char	*outfile;
	bool	append;
	bool	heredoc;
	char	*delimiter;
}			t_cmd;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;


// banner.c
void		ft_print_banner(void);
// signals.c
void		ft_set_signal_prompt_mode(void);
// exit.c
void		ft_exit_free_prompt(char *input);
// tokenizer.c
t_token		*ft_tokenizer(char *input);
// tokenizer_utils.c
int			ft_is_quote(char c);
int			ft_is_operator(char c);
// token.c
t_token		*ft_init_token(char *content);
// parser.c
void		ft_parser(t_token *token);
// parser_utils.c
int			ft_check_start_end_types(t_token *token);
int			ft_check_delimiters(t_token *token);
int			ft_check_redirects(t_token *token);

#endif
