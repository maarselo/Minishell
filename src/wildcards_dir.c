/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:29:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 21:20:54 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_dir(char *pattern, char **dir_name, char **name_pattern)
{
	char	*slash;

	*dir_name = NULL;
	*name_pattern = NULL;
	slash = ft_strrchr(pattern, '/');
	if (!slash)
	{
		*dir_name = ft_strdup("./");
		if (!*dir_name)
			return ;
		*name_pattern = ft_strdup(pattern);
		if (!*name_pattern)
			return (free(*dir_name));
	}
	else
	{
		*dir_name = ft_strndup(pattern, slash - pattern + 1);
		if (!*dir_name)
			return ;
		*name_pattern = ft_strdup(slash + 1);
		if (!*name_pattern)
			return (free(*dir_name));
	}
}

void	ft_match_case1(int *cmd_pattern_i, int *str_backup_i,
			int *cmd_i, int *str_i)
{
	*cmd_pattern_i = *cmd_i;
	*str_backup_i = *str_i;
	(*cmd_i)++;
}

void	ft_match_case2(int *cmd_i, int *str_i)
{
	(*cmd_i)++;
	(*str_i)++;
}

void	ft_match_case3(int *cmd_pattern_i, int *str_backup_i,
			int *cmd_i, int *str_i)
{
	*cmd_i = *cmd_pattern_i + 1;
	*str_i = *str_backup_i + 1;
	(*str_backup_i)++;
}
