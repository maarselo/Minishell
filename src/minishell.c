/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/26 23:52:39 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_status;

void	ft_process_input(char *input)
{
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
		ft_print_command_list(command_list);
		ft_free_command_list(command_list);
	}
}

void	ft_input_loop(char **envp)
{
	char	*input;

	(void)envp;
	ft_set_signal_prompt_mode();
	while (true)
	{
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
			ft_process_input(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (0);
	ft_set_global_exit_status(0);
	ft_print_banner();
	ft_input_loop(envp);
}
