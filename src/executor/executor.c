/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:36:40 by ecaruso           #+#    #+#             */
/*   Updated: 2024/01/16 19:47:03 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void execute_commands(t_mini *mini) {
    t_cmds *cmd = mini->cmds;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    while (cmd) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (cmd->redirect) {
                if (cmd->redirect->infile) {
                    dup2(mini->fdin, STDIN_FILENO);
                    close(mini->fdin);
                }
                if (cmd->redirect->outfile) {
                    dup2(mini->fdout, STDOUT_FILENO);
                    close(mini->fdout);
                }
            }

            execvp(cmd->cmd, cmd->args);
            perror("Execvp failed");
            fprintf(stderr, "Command: %s\n", cmd->cmd);
            fprintf(stderr, "Arguments:\n");
            char **args = cmd->args;
            while (*args) {
                fprintf(stderr, "  %s\n", *args++);
            }
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("Exit Status: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Terminated by Signal: %d\n", WTERMSIG(status));
            } else {
                printf("Unknown termination\n");
            }
            //exit(EXIT_SUCCESS);

            }

        cmd = cmd->next;
    }

    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdin);
    close(saved_stdout);
}
*/

char	*find_path(t_mini *mini, char **env)
{
	struct stat	buff;
	int			i;
	char		**base;
	char		*temp;
	char		*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while (base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
		if (!lstat(ft_strjoin(temp, mini->toks[0]), &buff))
		{
			path = ft_strjoin(temp, mini->toks[0]);
			free(temp);
			return (path);
		}
	}
	free(temp);
	return (NULL);
}

//funzione da cancellare
void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	printf("check");
	while (matrix[i])
	{
		printf("posizione matrice:%i\ncontenuto matrice:%s\n", i, matrix[i]);
		i++;
	}
	return ;
}

void	execute_commands(t_mini *mini)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = find_path(mini, mini->env);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("J\n");
		execve(path, mini->toks, mini->env);
		printf("K\n");
		perror("Execve failed");
		printf("L\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("M\n");
		if (WIFEXITED(status))
			printf("PORCODIO %d\n", WEXITSTATUS(status));
		else
			printf("PORCODEDDIO\n");
	}
}
