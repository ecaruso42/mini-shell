/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:16:01 by grinella          #+#    #+#             */
/*   Updated: 2023/12/06 17:59:11 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_redirect
{
    char *infile;          // <
    char *outfile;         // >, >>
    int redirect_type;     // 1 >, 2 >>, 3 <
} t_redirect;

typedef struct s_cmds
{
    char *cmd;              // init to NULL
    char **args;            // init to NULL
    t_redirect *redirect;
    int fdi;
    int fdo;
    struct s_cmds *next;
} t_cmds;

typedef struct s_mini
{
    t_cmds *cmds;
    int cmds_count;
    int fdin;                // init to NULL
    int fdout;               // init to NULL
    char **env;              // (full_path)
    char **toks;             // (full_cmds)
    char *str;
} t_mini;

typedef struct s_lexer {
    char **toks; // Token array
    int toks_count; // Number of tokens
    int args;
    int redirect;
} t_lexer;

//SEGNALI
int open_next_file(const char *filename);
void handle_signal(int signal);

//PARSER
int parse_input(t_mini *mini);

//EXECUTOR
//void execute_commands(t_mini *mini, char **env);
void execute_commands(t_mini *mini);
void free_cmd(t_cmds *cmd);
void initialize_lex(t_lexer *lex);
int run_lexer(const char *command, t_lexer *lexer);
t_mini *initialize_mini(t_mini *mini);
void handle_redirection(t_mini *mini, t_cmds *current_cmd);
int	get_env(char **envp, t_mini *mini);

#endif