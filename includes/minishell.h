/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/19 21:03:15 by fbanzo-s         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			heredoc;
	char			*delimiter;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// banner.c
void		ft_print_banner(void);
// signals.c
void		ft_set_signal_prompt_mode(void);
// minishell.c
// to print all time minshell and get the input
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
// parser_utils.c
int			ft_check_start_end_types(t_token *token);
int			ft_check_delimiters(t_token *token);
int			ft_check_redirects(t_token *token);
//int		ft_count_command(t_token *token_list);
// parser.c
t_cmd		*ft_parser(t_token *token);
// expander.c
void		ft_expand(t_cmd *cmd, t_env *env_list, int status);
t_env		*ft_get_env(char **envp);
// expander_utils.c
char		*ft_join_char_var(char *str, char c);
char		*ft_join_str_var(char *str, char *to_append);
// env.c
t_env		*ft_init_env(char *env_var);
// exit.c
void		ft_exit_free_prompt(char *input);

#endif
