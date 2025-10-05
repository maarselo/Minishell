/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 00:03:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>

# define MODE_READ "r"
# define MODE_WRITE "w"
# define MODE_APPEND "a"

# define NO_VALUE "no_value"
# define NULL_VALUE "null_value"
# define WITH_VALUE "with_value"

/*
	minishell.h
	Extern global to manipulate exit status from the last command
*/
typedef enum exit_codes
{
	T_SUCCESS = 0,
	T_GENERAL_ERROR = 1,
	T_FILES = 1,
	T_SYNTAX = 2,
	T_NON_EXISTENT_DIRECTORY = 2,//cd
	T_DIRECTORY_PERMITS = 2,//cd
	T_EXECUTABLE_PERMITS = 126,
	T_COMMAND_NOT_FOUND = 127,
	T_SIGINT = 130,
	T_SIGQUIT = 131,
}			t_exit_types;

/*
sig_atomic_t → asegura que la lectura/escritura sea atómica
				(no se corta en medio).
volatile → asegura que cada vez que el programa use la variable,
				 lea/escriba desde memoria, no desde registro cacheado.
*/
typedef struct s_global
{
	volatile sig_atomic_t	exit_status;
	volatile sig_atomic_t	heredoc_status;
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

/*
	env.c
	Struct to manage transform char ** to linked_list,
	to manipualte variables.
*/
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/*
	executor.c
	Struct to save the real terminal fd, and the real stdout
*/
typedef struct s_saved_fd
{
	int			saved_stdin;
	int			saved_stdout;
}				t_saved_fd;

// signals.c
void		ft_set_signals_prompt_mode(void);
void		ft_set_signals_heredoc_mode(void);

// global.c
void		ft_set_init_global_variables(void);
void		ft_set_global_exit_status(int new_exit_code);
void		ft_set_global_heredoc_status(int heredoc_status);

//default_fd.c
t_saved_fd	ft_store_defaults_fd(void);
void		ft_close_defaults_fd(t_saved_fd *saved_fd);
void		ft_resturare_defaults_fd(t_saved_fd saved_fd);

// banner.c
void		ft_print_banner(void);
// minishell.c
void		ft_process_input(char *input, t_saved_fd saved_fd,
				t_env **env_list);
void		ft_input_loop(char **envp);

// tokenizer_utils.c
int			ft_is_quote(char c);
int			ft_is_operator(char c);
void		ft_check_new_token(t_token *new_token, char *input, t_token *top);
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

// parser_redirection_utils
int			ft_have_any_redirection(t_token *start, t_token *end);
void		ft_set_redirect_infile(int *malloc_error, t_token *token,
				t_redirect *redirections);
void		ft_set_redirect_heredoc(int *malloc_error, t_token *token,
				t_redirect *redirections);
void		ft_set_redirect_outfile(int *malloc_error, t_token *token,
				t_redirect *redirections);
void		ft_set_redirect_append(int *malloc_error, t_token *token,
				t_redirect *redirections);
// parser_utils.c
int			ft_count_command(t_token *token_list);
int			ft_check_if_end_command(t_token *token);
t_token		*ft_get_previos_token(bool first, t_token *start, t_token *to_find);
int			ft_get_if_its_redirection_type(t_token *t);
void		ft_add_command_into_list(t_command *new_command, t_command *top);
// init_parser_struct.c
t_command	*ft_create_command_struct(void);
t_redirect	*ft_create_redirection_struct(int *malloc_eror);
char		*ft_strdup_with_flag(int *malloc_error, const char *s);
char		**ft_alloc_argv_according_words(int *malloc_error, t_token *start,
				t_token *end);
// parser.c
t_command	*ft_tokens_to_command_struct(t_token *token_list);

/////////////////////////////////////////////////////////////////////
// expander.c
void		ft_expand(t_command *cmd, t_env *env_list);
char		*ft_expand_var(char *str, int *i, t_env *env_list);
// expander_utils.c
char		*ft_join_char_var(char *str, char c);
char		*ft_join_str_var(char *str, char *to_append);
char		*ft_expand_tilde(char *result, t_env *env_list);
char		*ft_handle_expansion(char *result, char *str, int *i,
				t_env *env_list);
char		*ft_get_env_value(t_env *env_list, char *name_var);
// wildcards.c
char		**ft_expand_wildcard(char *str);
char		**ft_join_wildcards(char **argv, int index, char **wc_expanded);
void		ft_execute_wildcards(t_command *cmd, int *i);
int			ft_match(char *cmd, char *str);
char		**ft_realloc_array(char **array, int size);
// wildcards_utils.c
char		**ft_empty_matches(char	*str);
int			ft_array_len(char **array);
void		ft_free_cmd(char **array);
char		**ft_loop_entries(DIR *dir, char *pattern, char **matches, char *dir_name);
// wildcards_dir.c
void		ft_split_dir(char *pattern, char **dir_name, char **name_pattern);
// env.c
t_env		*ft_get_env(char **envp);
// env_utils.c
int			ft_get_value_length(char *env_var, int i);
t_env		*ft_create_env_node(char *name, char *value);
void		ft_add_env_var(t_env **env_list, char *name, char *value);
int			ft_find_env_var_name(t_env *env_list, char *name);

// builtins.c
int			ft_isbuiltin(char *cmd);
void		ft_execute_builtin(t_command *cmd, t_env **env_list,
				t_command*list);
// bultins_echo.c
void		ft_echo(char **args);
// bultins_cd.c
void		ft_cd(char **args, t_env *env_list);
// builtins_pwd.c
void		ft_pwd(char **args);
// builtins_export_utils.c
char		*ft_split_name_var(char *str);
char		*ft_split_value_var(char *str);
void		ft_replace_env_var(t_env *env_list, char *name_var, char *new_val);
int			ft_export_single(char *cmd, t_env *env_list);
t_env		*ft_create_node_export_by_mode(char *mode, char *command, t_env *env_list);
// builtins_export.c
void		ft_export(char **command, t_env *env_list);
// builtins_unset.c
void		ft_unset(char **args, t_env **env_list);
// builtins_env.c
void		ft_env(char **args, t_env *env_list);

// executor.c
void		ft_executor(t_command *command_list, t_saved_fd saved_fd,
				t_env **env);
// executor_pipes.c
int			ft_manage_pipes(int *prev_pipe, t_command *current_command,
				t_command *command_list);
//executor_redirections.c
int			ft_manage_redirections(t_command *current_command);
//executor_command_utils.c
t_command	*ft_get_previous_command(t_command *find, t_command *command_list);
bool		ft_is_last_command(t_command *command);
//executor_utils.c
int			ft_get_env_size(t_env *env_list);
char		**ft_convert_list(t_env *env_list);

// exit.c
void		ft_free_exit(char *input);
void		ft_clean_parser_memory_exit(t_command *command,
				t_command *command_list, t_token *token_list);
void		ft_exit_handler(char *input);

//free_data.c
void		ft_free_data(t_env *env_list, t_command *command_list);
// free.c
void		ft_free_input_token(char *input, t_token *token_list);
void		ft_free_token_list(t_token *token_list);
void		ft_free_envp(t_env *envp);
void		ft_free_command_list(t_command *command_list);
void		ft_free_split(char **split);
void		ft_free_envp(t_env *envp);
// free.utils.c
void		ft_free_argv_command(char **argv_command);
void		ft_free_redirections_command(t_redirect *redirections);

//error
void		ft_error_creating_pipe(int *prev_pipe);
void		ft_error_opening_files(void);
// testinf
void		ft_print_tokens(t_token	*token);
void		ft_print_command_list(t_command	*command_list);

#endif