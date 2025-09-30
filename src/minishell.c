/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/09/23 16:20:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_status;

//Manejar exit difeerentes tipos
void	ft_process_input(char *input, t_saved_fd saved_fd, t_env *env_list)
{
	(void)env_list;
	t_command	*command_list;
	t_token		*token_list;

	add_history(input);
	token_list = ft_tokenizer(input);
	if (!token_list)
	{
		ft_free_token_and_input(input, token_list);
		return ;
	}
	if (ft_syntax(token_list))
	{
		ft_free_token_and_input(input, token_list);
		ft_set_global_exit_status(T_SYNTAX);
	}
	else
	{
		free(input);
		command_list = ft_tokens_to_command_struct(token_list);
		ft_free_token_list(token_list);
		ft_expand(command_list);
		ft_executor(command_list, saved_fd, env_list);
		ft_free_command_list(command_list);
	}
}

void	ft_input_loop(char **envp)
{
	char		*input;
	t_saved_fd	saved_fd;
	t_env		*env_list;

	env_list = ft_get_env(envp);
	saved_fd = ft_store_defaults_fd();
	while (true)
	{
		ft_set_signals_prompt_mode();
		input = readline("\033[1;32mminishell $\033[0m ");
		if (!input)
			ft_exit_free_input(input);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (!ft_strncmp(input, "exit", ft_strlen("exit") + 1))
			ft_exit_free_input(input);
		if (*input)
			ft_process_input(input, saved_fd, env_list);
	}
	ft_free_envp(env_list);
	ft_close_defaults_fd(&saved_fd);
}

void	ft_set_init_global_variables(void)
{
	ft_set_global_exit_status(T_SUCCESS);
	ft_set_global_heredoc_status(0);//To init.
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (0);
	ft_print_banner();
	ft_input_loop(envp);
}
