/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:     :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/18 14:01:29 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_argv_command(char **argv_command)
{
	int	i;

	i = 0;
	if (!argv_command || !*argv_command)
		return ;
	while (argv_command[i])
	{
		free(argv_command[i]);
		i++;
	}
	free(argv_command);
	argv_command = NULL;
}

void	ft_free_redirections_command(t_redirect *redirections)
{
	if (redirections->infile)
		free(redirections->infile);
	if (redirections->outfile)
		free(redirections->outfile);
	if (redirections->delimiter)
		free(redirections->delimiter);
	free(redirections);
	redirections = NULL;
}

void	ft_free_pid_array(t_data *data)
{
	if (!data->pid_array)
		return ;
	free(data->pid_array);
	data->pid_array = NULL;
}
