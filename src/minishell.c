/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 14:25:27 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_status;

void	ft_process_input(char *input, t_data *data)
{
	t_token		*token_list;

	add_history(input);
	token_list = ft_tokenizer(input, data);
	if (!token_list)
		return (ft_free_input_token(input, token_list),
			ft_set_global_exit_status(T_SUCCESS));
	else if (ft_syntax1(token_list) || ft_syntax2(token_list))
		return (ft_free_input_token(input, token_list),
			ft_set_global_exit_status(T_SYNTAX));
	else
	{
		ft_tokens_to_command_struct(token_list, data);
		ft_free_input_token(input, token_list);
		ft_expand(data);
		ft_executor(data);
		ft_free_command_list(data);
	}
}

void	ft_input_loop(t_env *env_list)
{
	char		*input;
	t_saved_fd	saved_fd;
	t_data		*data;

	saved_fd = ft_store_defaults_fd();
	data = ft_init_data(env_list, saved_fd);
	while (true)
	{
		ft_set_signals_prompt_mode();
		if (isatty(fileno(stdin)))
			input = readline("\033[1;32mminishell $\033[0m ");
		else
		{
			char *tmp = get_next_line(data->saved_fd.saved_stdin);
			input = ft_strtrim(tmp, "\n");
		}
		ft_check_null_input(input, data);
		if (ft_check_void_input(input))
			continue ;
		if (ft_check_if_its_exit(input))
			ft_exit_handler(input, data);
		if (*input)
			ft_process_input(input, data);
	}
	ft_free_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argv;
	if (argc != 1)
		return (0);
	ft_print_banner();
	ft_set_init_global_variables();
	env_list = ft_get_env(envp);
	ft_input_loop(env_list);
}
