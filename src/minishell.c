/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/03 19:57:50 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char	*input;

	signal(SIGINT, ft_sigint_handler);
	while (1)
	{
		input = readline("\033[1;32mminishell $\033[0m ");
		if (!input)
		{
			ft_printf("exit\n");
			free(input);
			break ;
		}
		if (strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			ft_printf("exit\n");
			free(input);
			break ;
		}
		ft_get_tokens(input);
		free(input);
	}
	return (0);
}
