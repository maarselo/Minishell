/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/17 21:41:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var()
{
	
}

char	*ft_expand_variables(char *str, t_env *env_list, int exit_status)
{
	int		i;
	char	*tmp;
	char	*result;

	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_expand_var();
			result = ;
			free(tmp);
		}
		else
			result = ;
	}
	return (result);
}

char	*ft_execute_expander(char *str, t_env *env_list, int exit_status)
{
	int	l;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (l >= 2 && str[0] == '\'' && str[l - 1] == '\'')
		return (ft_strndup(str + 1, l - 2));
	if (l >= 2 && str[0] == '"' && str[l - 1] == '"')
		return (ft_expand_variables(ft_strndup(str + 1, l - 2), env_list,
				exit_status));
	return (ft_expand_variables(str, env_list, exit_status));
}

void	ft_expand(t_cmd *cmd, t_env *env_list, int exit_status)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			cmd->argv[i] = ft_execute_expander(cmd->argv[i], env_list,
					exit_status);
			i++;
		}
		cmd = cmd->next;
	}
}
