/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 20:53:15 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	main(void)
{
	char	*input;
	
	signal(SIGINT, sigint_handler);
	
	while (1)
	{
		input = readline("\033[1;32mminishell $\033[0m ");
		if (!input)
		{
			printf("exit\n");
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
			printf("exit\n");
			free(input);
			break ;
		}
		free(input);
	}
	return (0);
}
