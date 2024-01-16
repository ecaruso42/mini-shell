/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:16:01 by grinella          #+#    #+#             */
/*   Updated: 2024/01/16 19:43:31 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOTE          0
# define NDIR           1
# define NPERM          2
# define NCMD           3
# define DUPERR         4
# define FORKERR        5
# define PIPERR         6
# define PIPENDERR      7
# define MEM            8
# define QUIS_DIROTE    9
# define NOT_DIR        10

# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_redirect
{
	char *infile;          // <
	char *outfile;         // >, >>
	int redirect_type;     // 1 >, 2 >>, 3 <
} t_redirect;

typedef struct s_cmds
{
	char			*cmd;              // init to NULL
	char			**args;            // init to NULL
	t_redirect		*redirect;
	int				fdi;
	int				fdo;
	int				redirect_count;
	struct s_cmds	*next;
} t_cmds;

typedef struct	s_prompt
{
	t_cmds	*cmds;
	char	**envp;
	char	*pwd;
}	t_prompt;

typedef struct s_mini
{
	t_cmds *cmds;
	int		cmds_count;
	int		fdin; // init to NULL
	int		fdout; // init to NULL
	char	**env; // (full_path)
	char	**toks; // (full_cmds)
	char	*str;
	int		toks_count;
	int		args;
	int		redirect;
} t_mini;

//SEGNALI
int		open_next_file(const char *filename);
void	handle_signal(int signal);

//PARSER
int		parse_input(t_mini *mini);

//EXECUTOR
void	execute_commands(t_mini *mini);
/*
void execute_commands(t_mini *mini);
*/
void	free_cmds(t_cmds *cmd);
void	initialize_lex(t_mini *lex);
int		run_lexer(const char *command, t_mini *lexer);
t_mini	*initialize_mini(char **envp);
void	handle_redirection(t_mini *mini, t_cmds *current_cmd);
int		get_env(char **envp, t_mini *mini);
char	*find_path(t_mini *mini, char **env);

//BUILTINS
char	*get_env_char(char *var, char **envp, int n);

int		my_exit(t_list *ncd, int *n);
int		my_cd(t_prompt *p);
int		my_echo(t_prompt *p);
;
;
;
;
#endif