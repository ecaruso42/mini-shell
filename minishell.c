/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:57:44 by grinella          #+#    #+#             */
/*   Updated: 2024/01/16 20:04:10 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_mini	*initialize_mini(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		perror("Brutto STronzo");
		exit(EXIT_FAILURE);
	}
	mini->cmds = NULL;
	mini->fdin = STDIN_FILENO;
	mini->fdout = STDOUT_FILENO;
	mini->env = envp;
	mini->toks = 0;
	mini->toks_count = 0;
	mini->args = 0;
	mini->redirect = 0;
	return (mini);
}

void	free_cmd(t_cmds *cmd)
{
	free(cmd->cmd);
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i] != NULL; i++) //norminette for to while
		{
			free(cmd->args[i]);
		}
		free(cmd->args);
	}
	if (cmd->redirect)
	{
		free(cmd->redirect->infile);
		free(cmd->redirect->outfile);
		free(cmd->redirect);
	}
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*input;
	t_mini		*mini;

	printf("A\n");
	(void)argc;
	(void)argv;
	mini = initialize_mini(envp);
	//int		i;
	//initialize_mini(envp);
	get_env(envp, mini);
	printf("B\n");
	while (1)
	{
		printf("C\n");
		input = readline("shell>> ");
		if (input == NULL)
		{
			printf("exit");
			exit(1);
		}
		printf("D\n");
		if (input && input[0])
		{
			add_history(input);
			printf("E\n");
		}
		if (input && input[0])
		{
			printf("F\n");
			if (run_lexer (input, mini))
			{
				printf("G\n");
				if (parse_input(mini))
				{
					printf("H\n");
					execute_commands(mini);
					printf("I\n");
				}
			}
		}
		//free_cmds(&mini, input);
	}
	return (0);
}
