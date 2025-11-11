/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/08 18:08:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_input_terminal_free_data(t_data *data)
{
	ft_putstr_fd("\033[1;34mminishell\033[0m: input is not a terminal\n", 2);
	ft_free_data(data);
	exit(1);
}

static char	*ft_strjoin_multi(int total_str, ...)
{
	char	*join;
	char	*tmp;
	va_list	args;
	int		i;

	i = 0;
	join = ft_strdup("");
	va_start(args, total_str);
	while (++i <= total_str)
	{
		tmp = join;
		join = ft_strjoin(join, va_arg(args, char *));
		free(tmp);
	}
	va_end(args);
	return (join);
}

static char	*ft_cut_hostname(char *hostname_buffer)
{
	char	*ptr;

	ptr = ft_strchr(hostname_buffer, '.');
	return (ft_substr(hostname_buffer, 0, ptr - hostname_buffer));
}

static char *ft_cut_current_path(char *current_path, t_data *data)
{
	int		index;
	int		count;
	char	*path_without_home;
	char	*final_path;

	index = 0;
	count = 0;
	while (current_path[index])
	{
		if (count >= 3)
			break ;
		if (current_path[index] == '/')
			count++;
		if (count == 3)
			continue ;
		index++;
	}
	path_without_home = ft_substr(current_path, index, ft_strlen(current_path) - index);
	if (!path_without_home)
		return (ft_perror_free_data_exit(data, T_GENERAL_ERROR), NULL);
	final_path = ft_strjoin("~", path_without_home);
	if (!final_path)
		return (ft_perror_free_data_exit(data, T_GENERAL_ERROR), NULL);
	return (free(path_without_home), final_path);
}

char	*ft_acces_env_value(char *name_var, t_env *env_list)
{
	t_env	*env_node;

	env_node = env_list;
	while (env_node)
	{
		if (ft_strcmp(env_node->name, name_var) == 0)
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}

char	*ft_get_input(t_data *data)
{
	char	host_buffer[1024];
	char	current_path[1024];
	char	*final_path;
	char	*hostname;
	char	*prompt;
	char	*input;

	if (!isatty(STDIN_FILENO))
		ft_error_input_terminal_free_data(data);
	if (getcwd(current_path, sizeof(current_path)) == NULL)
		return (readline("\033[1;34mminishell \033[0m"));
	if (!ft_acces_env_value("USER", data->env)
		|| gethostname(host_buffer, sizeof(host_buffer)) == -1
		|| !ft_acces_env_value("PWD", data->env))
		return (readline("\033[1;34mminishell \033[0m"));
	hostname = ft_cut_hostname(host_buffer);
	final_path = ft_cut_current_path(current_path, data);
	prompt = ft_strjoin_multi(8, "\033[1;34m",
			ft_acces_env_value("USER", data->env), "@", hostname, ":",
			final_path, "$ ", "\033[0m");
	input = readline(prompt);
	return (free(hostname), free(prompt), free(final_path), input);
}
