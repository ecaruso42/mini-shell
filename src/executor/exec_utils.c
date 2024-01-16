#include  "../../includes/minishell.h"

/*
int find_env_index(char **env, const char *var)
{
    int index = 0;
    while (env[index] != NULL) {
        if (strncmp(env[index], var, strlen(var)) == 0 && env[index][strlen(var)] == '=') {
            return index;
        }
        index++;
    }
    return -1;
}

int find_binary_path(t_mini *mini, t_cmds *cmds)
{
    int index = 0;
    while (mini->env[index] != NULL) {
        if (strncmp(mini->env[index], "PATH=", 5) == 0) {
            char *path = mini->env[index] + 5;
            char *token = strtok(path, ":");
            while (token != NULL) {
                char *full_path = malloc(strlen(token) + strlen(cmds->cmd) + 2);
                if (full_path == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                sprintf(full_path, "%s/%s", token, cmds->cmd);
                if (access(full_path, X_OK) == 0) {
                    return index;
                }
                free(full_path);
                token = strtok(NULL, ":");
            }
        }
        index++;
    }
    return -1;
}

char *add_path_to_command(t_mini *mini, t_cmds *cmds, int index)
{
    char *path = mini->env[index] + 5;
    char *full_path = malloc(strlen(path) + strlen(cmds->cmd) + 2);
    if (full_path == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf(full_path, "%s/%s", path, cmds->cmd);
    return full_path;
}

// Function to execute a command using execve after checking whether it's a built-in command or an external binary
void execute(t_mini *mini, t_cmds *cmds)
{
    if (strcmp(cmds->cmd, "cd") == 0)
    {
        // Handle cd as a built-in command
        if (cmds->args[1] != NULL)
        {
            if (chdir(cmds->args[1]) == -1)
            {
                perror("cd");
            }
        }
    } else if (strcmp(cmds->cmd, "exit") == 0)
    {
        // Handle exit as a built-in command
        exit(EXIT_SUCCESS);
    } else
    {
        int index = find_binary_path(mini, cmds);
        if (index != -1)
        {
			printf("check\n");
            char *full_path = add_path_to_command(mini, cmds, index);
            execve(full_path, cmds->args, mini->env);
            perror("execve");
            free(full_path);
        } else
        {
            fprintf(stderr, "Error: Command not found\n");
            exit(EXIT_FAILURE);
        }
    }
}


void handle_here_document(t_mini *mini, const char *delimiter)
{
    (void)mini;
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("<< ");
        ssize_t read_bytes = getline(&line, &len, stdin);
        if (read_bytes == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (strcmp(line, delimiter) == 0) {
            break;
        }
    }

    free(line);
}

// Function to handle input (<) and output (>, >>) redirection
void handle_redirection(t_mini *mini, t_cmds *current_cmd)
{
    if (current_cmd->redirect->infile != NULL) {
        mini->fdin = open(current_cmd->redirect->infile, O_RDONLY);
        if (mini->fdin == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    if (current_cmd->redirect->outfile != NULL) {
        int flags;
        if (current_cmd->redirect->redirect_type == 1) {
            flags = O_WRONLY | O_CREAT | O_TRUNC;
        } else {
            flags = O_WRONLY | O_CREAT | O_APPEND;
        }

        mini->fdout = open(current_cmd->redirect->outfile, flags, 0666);
        if (mini->fdout == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to update file descriptors based on redirection information
void update_file_descriptors(t_mini *mini, t_cmds *current_cmd)
{
    if (current_cmd->fdi != -1) {
        dup2(current_cmd->fdi, STDIN_FILENO);
        close(current_cmd->fdi);
    } else {
        dup2(mini->fdin, STDIN_FILENO);
        close(mini->fdin);
    }

    if (current_cmd->fdo != -1) {
        dup2(current_cmd->fdo, STDOUT_FILENO);
        close(current_cmd->fdo);
    } else {
        dup2(mini->fdout, STDOUT_FILENO);
        close(mini->fdout);
    }
}

// Function to close file descriptors related to input and output
void close_file_descriptors(t_mini *mini)
{
    close(mini->fdin);
    close(mini->fdout);
}

// Function to execute multiple commands in a pipeline
void execute_pipeline(t_mini *mini)
{
    t_cmds *cmd = mini->cmds;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int pipe_fd[2];

    while (cmd) {
        if (cmd->next) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            cmd->fdo = pipe_fd[1];
            cmd->next->fdi = pipe_fd[0];
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close_file_descriptors(mini);
            update_file_descriptors(mini, cmd);
            execute(mini, cmd);
        } else {
            close(cmd->fdo);
            if (!cmd->next) {
                close(cmd->fdi);
            }
            waitpid(pid, NULL, 0);
        }

        cmd = cmd->next;
    }

    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdin);
    close(saved_stdout);
}

// Main execution function
void execute_commands(t_mini *mini)
{
    t_cmds *cmd = mini->cmds;

    while (cmd)
    {
        // Handle here document redirection
        if (cmd->redirect && cmd->redirect->redirect_type == 3)
        {
            handle_here_document(mini, cmd->redirect->infile);
            cmd = cmd->next;
            continue;
        }

        // Handle input/output redirection
        handle_redirection(mini, cmd);

        // Execute multiple commands in a pipeline
        execute_pipeline(mini);

        cmd = cmd->next;
    }
}
*/