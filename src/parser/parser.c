/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:48:05 by ecaruso           #+#    #+#             */
/*   Updated: 2024/01/16 19:58:54 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parse	*initialize_parser(void)
{
	t_parse	*parser;

	parser = (t_parse *)malloc(sizeof(t_parse));
	if (parser == NULL)
	{
		exit(EXIT_FAILURE);
	}
	parser->toks = 0;
	parser->p_args = 0;
	parser->red = 0;
	parser->args = 0;
	return (parser);
}

t_cmds	*initialize_cmds(void)
{
	t_cmds	*cmds;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmds == NULL)
	{
		exit(EXIT_FAILURE);
	}
	cmds->cmd = NULL;
	cmds->args = (char **)malloc(sizeof(char *) * 1000);
	cmds->redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (cmds->redirect == NULL)
	{
		exit(EXIT_FAILURE);
	}
	cmds->redirect->infile = NULL;
	cmds->redirect->outfile = NULL;
	cmds->redirect->redirect_type = 0;
	cmds->fdi = 0;
	cmds->fdo = 0;
	cmds->redirect_count = 0;
	cmds->next = NULL;
	return (cmds);
}

int	open_next_file(const char *filename)
{
	int	fd;

	if (strcmp(filename, "<") == 0)
	{
		fprintf(stderr, "Error: Missing input file after '<'\n");
		exit(EXIT_FAILURE);
	}
	else if (strcmp(filename, ">") == 0)
	{
		fprintf(stderr, "Error: Missing output file after '>'\n");
		exit(EXIT_FAILURE);
	}
	else if (strcmp(filename, ">>") == 0)
	{
		fprintf(stderr, "Error: Missing output file after '>>'\n");
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	is_redirection(char *str)
{
	return (str && (str[0] == '<' || str[0] == '>'
			|| (str[1] && str[1] == '>')));
}

int	count_total_redirection(t_mini *mini, int i)
{
	while (mini->toks[i] && is_redirection(mini->toks[i]))
	{
		i++;
	}
	return (i);
}

int	count_total_args(t_mini *mini, t_parse *parser)
{
	int	count;

	count = 0;
	while (mini->toks[parser->args] && !is_redirection(mini->toks[parser->args])
		&& strcmp(mini->toks[parser->args], "|") != 0)
	{
		parser->args++;
		count++;
	}
	return (count);
}

int	count_redirection_toks(t_mini *mini, t_parse *parser)
{
	int	count;

	count = 0;
	while (mini->toks[parser->red] && is_redirection(mini->toks[parser->red]))
	{
		parser->red++;
		count++;
	}
	return (count);
}

/*void initialize_cmds(t_cmds *cmds, int args_count, int redirect_count)
{
	cmds->cmd = NULL;

	cmds->args = malloc((args_count + 1) * sizeof(char *));
	cmds->args[args_count] = NULL;

	cmds->redirect = malloc(sizeof(t_redirect) * redirect_count);

	cmds->fdi = 0;
	cmds->fdo = 1;
	cmds->next = NULL;
}*/

int handle_redirection_1(t_cmds *cmds, char **toks, t_parse *parser, int i)
{
	(void)parser;
	if (!toks[i + 1] || strcmp(toks[i + 1], "|") == 0)
	{
		printf("Error: Missing argument for redirection.\n");
		return (-1);
	}
	if (is_redirection(toks[i + 1]))
		i++;
	else
	{
		cmds->redirect->outfile = toks[i + 1];
		if (toks[i][0] == '>')
			cmds->redirect->redirect_type = 1;
		else
			cmds->redirect->redirect_type = 3;
		cmds->redirect->infile = NULL;
		cmds->redirect_count++;
		cmds->fdo = 1;
		i += 2;
	}
	return (i);
}

int	handle_redirection_2(t_cmds *cmds, char **toks, t_parse *parser, int i)
{
	(void)parser;
	if (!toks[i + 1] || strcmp(toks[i + 1], "|") == 0)
	{
		printf("Error: Missing argument for redirection.\n");
		return (-1);
	}
	if (is_redirection(toks[i + 1]))
		i++;
	else
	{
		cmds->redirect->infile = toks[i + 1];
		cmds->redirect->redirect_type = 3;
		cmds->redirect->outfile = NULL;
		cmds->redirect->redirect_type = 0;
		cmds->redirect_count++;
		cmds->fdi = 1;
		i += 2;
	}
	return (i);
}

// Function to handle adding the last command in the command sequence to the cmds structure
void	handle_last_command(t_mini *mini, t_parse *parser, t_cmds *cmds)
{
	initialize_cmds();
	if (cmds->cmd == NULL)
	{
		printf("%s\n", mini->toks[0]);
		cmds->cmd = ft_strdup(mini->toks[parser->toks]);
		cmds->args[0] = ft_strdup(cmds->cmd);
		parser->toks++;
	}
	{
		while (mini->toks[parser->toks]
			&& ft_strncmp(mini->toks[parser->toks], "|", 1)
			&& !is_redirection(mini->toks[parser->toks]))
		{
			cmds->args[parser->p_args] = ft_strdup(mini->toks[parser->toks]);
			parser->toks++;
		}
	}
	parser->p_args++;
	cmds->args[parser->p_args] = NULL;
}

// Function to create a new command in the linked list of commands
t_cmds	*create_new_command(void)
{
	t_cmds	*new_cmd;

	new_cmd = malloc(sizeof(t_cmds));
	if (!new_cmd)
		exit(EXIT_FAILURE);
	new_cmd->redirect = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*void initialize_lex(t_lexer *lex) {
	lex->toks_count = 0;
	lex->args = 0;
	lex->redirect = 0;

}*/

int	parse_input(t_mini *mini)
{
	t_cmds	*head;
	t_cmds	*current;
	t_parse	*parser;
	int		i;

	head = initialize_cmds();
	current = head;
	parser = initialize_parser();
	i = 0;
	while (mini->toks[i])
	{
		if (strcmp(mini->toks[i], "|") == 0)
		{
			current->next = initialize_cmds();
			current = current->next;
			parser->args++;
		}
		else if (is_redirection(mini->toks[i]))
		{
			if (mini->toks[i][0] == '>')
				i = handle_redirection_1(current, mini->toks, parser, i);
			else if (mini->toks[i][0] == '<')
				i = handle_redirection_2(current, mini->toks, parser, i);
			if (i == -1)
				return (-1);
		}
		else
		{
			handle_last_command(mini, parser, current);
		}
		i++;
	}
	return (1);
}

/*int	parse_input(t_mini *mini)
{
	t_parse	parser;
	t_cmds		*cmds;
	t_cmds		*head;

	initialize_parser();
	cmds = ft_calloc(sizeof(t_cmds), 1);
	head = cmds;
	initialize_cmds();
	while (mini->toks[parser.toks])
	{
		if (ft_strncmp(mini->toks[parser.toks], "|", 1) == 0)
		{
			if (mini->toks[parser.toks + 1] == NULL)
				return (-1);
			mini->cmds_count++;
			parser.p_args = 0;
			cmds->next = ft_calloc(sizeof(t_cmds), 1);
			cmds = cmds->next;
			parser.red++;
			initialize_cmds();
			parser.toks++;
		}
		else if (!ft_strncmp(mini->toks[parser.toks], ">>", 2))
		{
			if (handle_redirection_1(cmds, mini->toks, &parser, 2) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.toks], ">", 1))
		{
			if (handle_redirection_1(cmds, mini->toks, &parser, 1) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.toks], "<<", 2))
		{
			if (handle_redirection_2(cmds, mini->toks, &parser, 4) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.toks], "<", 1))
		{
			if (handle_redirection_2(cmds, mini->toks, &parser, 3) == -1)
				return (-1);
		}
		else
			handle_last_command(mini, &parser, cmds);
	}
	mini->cmds = head;
	return (1);
}*/