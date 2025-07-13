/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/13 19:55:36 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_input(char *input, t_env *env_list)
{
	t_cmd	*cmd_list;
	t_token	*token_list;
	int		status;

	status = 0;
	add_history(input);
	token_list = ft_tokenizer(input);
	//cmd_list = ft_parser(token_list);
	ft_expand(cmd_list, env_list, status);
	ft_free_token(token_list);
	free(input);
}

void	ft_input_loop(char **envp)
{
	char	*input;
	t_env	*env_list;

	(void)envp;
	ft_set_signal_prompt_mode();
	env_list = ft_get_env(envp);
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
			ft_process_input(input, env_list);
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
