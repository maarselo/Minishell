/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:29:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 00:07:28 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_dir(char *pattern, char **dir_name, char **name_pattern)
{
	char	*slash;

	slash = ft_strrchr(pattern, '/');
	if (!slash)
	{
		*dir_name = ft_strdup("./");
		*name_pattern = ft_strdup(pattern);
	}
	else
	{
		*dir_name = ft_strndup(pattern, slash - pattern + 1);
		*name_pattern = ft_strdup(slash + 1);
	}
}
