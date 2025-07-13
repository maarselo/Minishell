/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/12 22:50:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_syntax(token_list);
			//free(token_list)
			free(input);
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
