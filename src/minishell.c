/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/11 15:01:30 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_status;

void	ft_input_loop(char **envp)
{
	char	*input;
	t_token	*token_list;

	(void)envp;
	ft_set_signal_prompt_mode();
	while (true)
	{
		input = readline("\033[1;32mminishell $\033[0m ");
		if (!input)
			ft_exit_free_prompt(input);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
            ft_exit_free_prompt(input);
		if (*input)
		{
			add_history(input);
			token_list = ft_tokenizer(input);
			if (ft_syntax(token_list))
			{
				ft_free_token_and_input(input, token_list);
				ft_set_global_exit_status(T_SYNTAX);
				continue ;
			}
			//ft_tokens_to_command_struct(token_list);
			ft_free_token_and_input(input, token_list);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (0);
	ft_print_banner();
	ft_input_loop(envp);
}
