/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:40:07 by ecaruso           #+#    #+#             */
/*   Updated: 2024/01/16 20:02:02 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	tokenize_command(const char *command, t_mini *lexer)
{
	char	*token;
	int		token_start;
	int		in_quote;
	int		i;
	int		count;

	token = NULL;
	token_start = 0;
	in_quote = 0;
	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			if (!in_quote)
			{
				in_quote = command[i];
				token_start = i + 1;
			}
			else if (in_quote == command[i])
			{
				in_quote = 0;
				token = strndup(command + token_start, i - token_start);
			}
		}
		else if (is_whitespace(command[i]) && !in_quote)
		{
			if (token_start < i)
			{
				token = strndup(command + token_start, i - token_start);
			}
		}
		else if (command[i] == '|' || command[i] == '<' || command[i] == '>')
		{
			if (!in_quote)
			{
				if (token_start < i)
				{
					token = strndup(command + token_start, i - token_start);
				}
			}
			token = strndup(command + i, 1);
			token_start = i + 1;
		}
		if (token != NULL)
		{
			count = lexer->toks_count;
			lexer->toks = realloc(lexer->toks, (count + 2) * sizeof(char *));
			lexer->toks[count] = token;
			lexer->toks[count + 1] = NULL;
			lexer->toks_count++;
			token = NULL;
		}
		++i;
	}
	if (token_start < (int)ft_strlen(command))
	{
		token = strndup(command + token_start, strlen(command) - token_start);
		count = lexer->toks_count;
		lexer->toks = realloc(lexer->toks, (count + 2) * sizeof(char *));
		lexer->toks[count] = token;
		lexer->toks[count + 1] = NULL;
		lexer->toks_count++;
	}
}

int	get_env(char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	if (!mini->env)
		return (1);
	i = 0;
	while (envp && envp[0] && envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->env[i] = NULL;
	return (0);
}

void	lexer_main(const char *command, t_mini *lexer)
{
	lexer->toks = malloc(sizeof(char *));
	lexer->toks[0] = NULL;
	lexer->toks_count = 0;
	tokenize_command(command, lexer);
}

int	run_lexer(const char *command, t_mini *lexer)
{
	lexer->toks = NULL;
	lexer->toks_count = 0;
	lexer_main(command, lexer);
	free((void *)command);
	if (lexer->toks_count > 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
