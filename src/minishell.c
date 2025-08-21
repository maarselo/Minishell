/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/21 22:09:25 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_input(char *input, t_env *env_list)
{
	t_cmd	*cmd_list;
	t_token	*token_list;
	int		status;
	int j;

	status = 0;
	add_history(input);

	// Tokenización
	token_list = ft_tokenizer(input);

	// Aquí normalmente harías:
	// cmd_list = ft_parser(token_list);
	// Pero como el parser no está hecho, vamos a hacer un comando fake:
	cmd_list = malloc(sizeof(t_cmd));
	if (!cmd_list)
		return ;
	cmd_list->argv = (char *[]){
		ft_strdup("echo"),
		ft_strdup("Hola,"),
		ft_strdup("$?"),
		ft_strdup("y tu \'nombre es $USER ~/test \'"),
		ft_strdup("\'$HOME\'"),
		NULL
	};
	cmd_list->infile = ft_strdup("$HOME/input.txt");
	cmd_list->outfile = ft_strdup("$HOME/output.txt");
	cmd_list->append = false;
	cmd_list->heredoc = true;
	cmd_list->delimiter = ft_strdup("$SJDFAS");
	cmd_list->next = NULL;

	// Expansión de variables en todos los comandos de la lista
	ft_expand(cmd_list, env_list, status);
while (cmd_list)
	{
		j = 0;
		printf("Comando:\n");
		while (cmd_list->argv && cmd_list->argv[j])
		{
			printf("  argv[%d] = %s\n", j, cmd_list->argv[j]);
			j++;
		}
		if (cmd_list->infile)
			printf("  infile: %s\n", cmd_list->infile);
		if (cmd_list->outfile)
			printf("  outfile: %s\n", cmd_list->outfile);
		if (cmd_list->delimiter)
			printf("  delimiter: %s\n", cmd_list->delimiter);
		printf("  append: %d, heredoc: %d\n", cmd_list->append, cmd_list->heredoc);
		cmd_list = cmd_list->next;
	}
	// --- FIN DEBUG ---
}

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
