/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 18:29:13 by fbanzo-s         ###   ########.fr       */
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

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}	t_token;


//banner
void	ft_print_banner(void);

//signals
void	ft_set_signal_prompt_mode(void);//Change ctrl c to display new line and ignore ctrl \.

//mains
void	ft_input_loop(char **envp);//to print all time minshell and get the input


//init token
t_token	*ft_init_token(char *content);
//tokenizerutils /tokenizer
int	ft_is_quote(char c);
int	ft_is_operator(char c);
char *ft_extract_token(char *input, int *i);

t_token	*ft_tokenizer(char *input);


//parser utils/parser
int	ft_count_command(t_token *token_list);

void	ft_parser(t_token *token);


//exits
void	ft_exit_free_prompt(char *input);//Ctrl + D, type exit


//int	ft_find_char(int c, char *input);//for find "" and '' to see if there are peers
//int	ft_check_quotes(char *input);


#endif
