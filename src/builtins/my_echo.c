/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:23 by grinella          #+#    #+#             */
/*   Updated: 2024/01/15 17:56:36 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_echo(t_prompt *p)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	// Gestisce l'opzione -n per non stampare il carattere di nuova riga alla fine.
	if (((t_mini *)p->cmds->content)->toks && \
		!ft_strncmp(((t_mini *)p->cmds->content)->toks[1], "-n", 2))
	{
		newline = 0;
		i++;
	}
	// Stampa gli argomenti separati da spazi sulla console.
	while (((t_mini *)p->cmds->content)->toks && \
		((t_mini *)p->cmds->content)->toks[i])
	{
		ft_putstr_fd(((t_mini *)p->cmds->content)->toks[i], 1);
		if (((t_mini *)p->cmds->content)->toks[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	// Stampa una nuova riga se l'opzione -n non è specificata.
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int main ()
{
	
}