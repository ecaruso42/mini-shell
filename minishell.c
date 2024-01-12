/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:57:44 by grinella          #+#    #+#             */
/*   Updated: 2024/01/06 02:01:56 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_mini *initialize_mini(char    **envp)
{
    mini = malloc(sizeof(t_mini));
    if (!mini) 
    {
        perror("Error initializing mini shell");
        exit(EXIT_FAILURE);
    }

    mini->cmds = NULL;
    mini->fdin = STDIN_FILENO;
    mini->fdout = STDOUT_FILENO;
    mini->env = envp;
    mini->toks = 0;

    return mini;
}

void free_cmd(t_cmds *cmd)
{
    free(cmd->cmd);
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i] != NULL; i++)
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
    (void)argc;
    (void)argv;
	const char	*input;
	t_mini	*mini;
	int		i;

	get_env(envp, &mini);
	while (1)
	{
		initialize_mini(envp);
		//sig_ignore(&mini);
		input = readline("BASH$: ");
		add_history(input);
		if (run_lexer (input, &mini))
		{
			if (parser_input(&mini))
				execute_commands(&mini);
		}
		free_cmds(&mini, input);
	}
	return (0);
}

/*int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;

    t_mini *mini = initialize_mini(envp);

    while (1) {
        char *input = readline("shell% ");
        if (!input)
        {
            printf("\n");
            exit(0);
        }
        add_history(input);
        mini->toks = NULL;
        t_lexer lexer;
        initialize_lex(&lexer);
        run_lexer(input, &lexer);
        if (parse_input(mini) != -1) 
        {
            execute_commands(mini);//, envp);
        }
        
        int i = 0;
        while (mini->toks[i] != NULL) 
        {
            free(mini->toks[i]);
            i++;
        }
        free(mini->toks);

        free(input);
    }

    return 0;
}*/

