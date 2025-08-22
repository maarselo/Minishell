/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 02:49:29 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_process_input(char *input, t_env *env_list)
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
}*/

t_command	*create_test_command(char **argv)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->command = argv; 
    cmd->redirection = NULL;
    cmd->connector = 0;
    cmd->next = NULL;
    return (cmd);
}

char	**duplicate_argv(const char **argv)
{
    int		count;
	char	**new_argv;

	count = 0;
    while(argv[count])
        count++;
    new_argv = malloc(sizeof(char *) * (count + 1));
    if (!new_argv)
        return NULL;
    for (int i = 0; i < count; i++)
        new_argv[i] = ft_strdup(argv[i]);
    new_argv[count] = NULL;
    return (new_argv);
}

void	ft_process_input(char *input, t_env *env_list)
{
    (void)input;
    t_command *cmd_list = NULL;
    t_command *current = NULL;

    int status = 0; // You can change this to test `$?`
    // --- TEST CASE 1: Basic variable expansion ---
    char *argv1[] = {"echo", "Hola,", "$USER", NULL};
    current = create_test_command(duplicate_argv((const char **)argv1));
    cmd_list = current;
    // --- TEST CASE 2: No expansion with single quotes ---
    char *argv2[] = {"echo", "'$USER'", NULL};
    current->next = create_test_command(duplicate_argv((const char **)argv2));
    current = current->next;
    // --- TEST CASE 3: Mixed quotes and variable expansion
    char *argv3[] = {"echo", "\"y tu 'nombre' es $USER ~ \"", NULL};
    current->next = create_test_command(duplicate_argv((const char **)argv3));
    current = current->next;
    // --- TEST CASE 4: The exit status variable '$?' ---
    char *argv4[] = {"echo", "$?", NULL};
    current->next = create_test_command(duplicate_argv((const char **)argv4));
    current = current->next;
    // --- TEST CASE 5: Tilde expansion with a path
    char *argv5[] = {"echo", "~/Documents", NULL};
    current->next = create_test_command(duplicate_argv((const char **)argv5));
    current = current->next;
    // --- TEST CASE 6: Tilde in the middle of a word
    char *argv6[] = {"echo", "A~B", NULL};
    current->next = create_test_command(duplicate_argv((const char **)argv6));
    current = current->next;
    ft_expand(cmd_list, env_list, status);
    t_command *temp_cmd;
    while (cmd_list)
    {
        temp_cmd = cmd_list->next;
        // Print
        printf("Expanded command:\n");
        for (int i = 0; cmd_list->command[i]; i++)
        {
            printf("  argv[%d] = %s\n", i, cmd_list->command[i]);
            free(cmd_list->command[i]);
        }
        free(cmd_list->command);
        free(cmd_list);
        cmd_list = temp_cmd;
    }
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
