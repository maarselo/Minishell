/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 23:06:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_split_name_var(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}

char	*ft_split_value_var(char *str)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
		j++;
	}
	while (str[i])
	{
		l++;
		i++;
	}
	return (ft_substr(str, j + 1, l));
}

void	ft_replace_env_var(t_env *env_list, char *name_var, char *new_val)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name_var) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_val);
			break ;
		}
		current = current->next;
	}
}

int	ft_export_single(char *cmd, t_env *env_list)
{
    if (ft_isdigit(cmd[0]) || cmd[0] == '=' || ft_contains_metachar(cmd))
    {
        printf("minishell: export: `%s`: not a valid identifier\n", cmd);
        ft_set_global_exit_status(T_GENERAL_ERROR);
        return (1);
    }
    if (!ft_strchr(cmd, '=') && ft_is_all_asnum(cmd))
        return ft_create_and_add_variable(NO_VALUE, cmd, env_list);
    if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] == '=')
        return ft_create_and_add_variable(NULL_VALUE, cmd, env_list);
    if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] != '=')
        return ft_create_and_add_variable(WITH_VALUE, cmd, env_list);
    return 0;
}

t_env	*ft_create_node_export_by_mode(char *mode, char *command)
{
	t_env	*node_env;

	node_env = (t_env *)ft_calloc(1, sizeof(t_env));

	if (!ft_strcmp(mode, NO_VALUE))
	{
		node_env->name = ft_strdup(command);
		if (!node_env->name)
			return (perror("minishell :"), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		ft_set_global_exit_status(T_SUCCESS);
	}
	else if (!ft_strcmp(mode, NULL_VALUE))
	{
		node_env->name = ft_strndup(command, ft_strlen(command) - 1);
		if (!node_env->name)
			return (perror("minishell :"), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		node_env->value = ft_strdup("");
		if (!node_env->value)
			return (perror("minishell :"), free(node_env->name), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
	}
	else if (!ft_strcmp(mode, WITH_VALUE))
	{
		node_env->name = ft_substr(command, 0, ft_strchr(command, '=') - command);
		if (!node_env->name)
			return (perror("minishell :"), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		node_env->value = ft_substr(command, ft_strlen(node_env->name) + 1,
				ft_strlen(command) - ft_strlen(node_env->name) - 1);
		if (!node_env->value)
			return (perror("minishell: "), free(node_env->name), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
	}
	return (node_env);
}
